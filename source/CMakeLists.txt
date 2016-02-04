cmake_minimum_required(VERSION 3.0)

project (skeleton VERSION 0.0.1)

########################################################################

add_subdirectory(cucumber-cpp-0.3)

########################################################################

function(add_avr_executable EXECUTABLE_NAME)
  if(NOT ARGN)
    message(FATAL_ERROR "No source files given for ${EXECUTABLE_NAME}.")
  endif(NOT ARGN)

  set(elf_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.elf)
  set(hex_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.hex)

  add_executable(${elf_file} EXCLUDE_FROM_ALL ${ARGN})

  set_target_properties(
    ${elf_file}
    PROPERTIES
    COMPILE_FLAGS "-mmcu=${AVR_MCU} -DF_CPU=${AVR_F_CPU} -Os"
    LINK_FLAGS "-mmcu=${AVR_MCU}"
  )

  add_custom_command(
    OUTPUT ${hex_file}
    COMMAND
    ${AVR_OBJCOPY} -O ihex -R .eeprom ${elf_file} ${hex_file}
    DEPENDS ${elf_file}
  )

  add_custom_target(
    ${EXECUTABLE_NAME}
    ALL
    DEPENDS ${hex_file}
  )

  set_target_properties(
    ${EXECUTABLE_NAME}
    PROPERTIES
    OUTPUT_NAME "${elf_file}"
  )

endfunction(add_avr_executable)



add_subdirectory(fw)
add_subdirectory(fw-test)
add_subdirectory(fw-main)

########################################################################

add_definitions(
  -std=c++14
  )

add_subdirectory(gmock-1.7.0)

add_subdirectory(app)

########################################################################

add_subdirectory(app-test)
add_subdirectory(acceptance-test-host)

########################################################################

enable_testing()
add_test(NAME run-app-test COMMAND ws::app-test)

########################################################################

add_executable(skeleton
  main/main.cc
  )
add_executable(ws::skeleton ALIAS skeleton)

target_link_libraries(skeleton
  PRIVATE ws::app
  )
