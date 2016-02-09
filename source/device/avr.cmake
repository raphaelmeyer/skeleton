########################################################################

function(set_avr_executable_properties EXECUTABLE_NAME)
  if(CMAKE_SYSTEM_PROCESSOR STREQUAL "avr")

    set_target_properties(
      ${EXECUTABLE_NAME}
      PROPERTIES
      COMPILE_FLAGS "-mmcu=${AVR_MCU} -DF_CPU=${AVR_F_CPU} -Os"
      LINK_FLAGS "-mmcu=${AVR_MCU}"
    )

    set(HEX_FILE ${EXECUTABLE_NAME}.hex)

    add_custom_command(
      OUTPUT ${HEX_FILE}
      COMMAND ${AVR_OBJCOPY} -O ihex -R .eeprom ${EXECUTABLE_NAME} ${HEX_FILE}
      DEPENDS ${EXECUTABLE_NAME}
    )

  endif()
endfunction(set_avr_executable_properties)

########################################################################

function(set_avr_library_properties LIBRARY_NAME)
  if(CMAKE_SYSTEM_PROCESSOR STREQUAL "avr")

    set_target_properties(
      ${LIBRARY_NAME}
      PROPERTIES
      COMPILE_FLAGS "-mmcu=${AVR_MCU} -DF_CPU=${AVR_F_CPU} -Os"
    )

  else()

    target_include_directories(
      ${LIBRARY_NAME}
      PUBLIC seams
    )

  endif()
endfunction(set_avr_library_properties)

########################################################################

#[[
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

function(add_avr_library LIBRARY_NAME)
  if(NOT ARGN)
    message(FATAL_ERROR "No source files given for ${LIBRARY_NAME}.")
  endif(NOT ARGN)

  set(lib_file ${LIBRARY_NAME}${MCU_TYPE_FOR_FILENAME})

  add_library(${lib_file} ${ARGN})

  set_target_properties(
    ${lib_file}
    PROPERTIES
    COMPILE_FLAGS "-mmcu=${AVR_MCU} -DF_CPU=${AVR_F_CPU} -Os"
    OUTPUT_NAME "${lib_file}"
  )

  if(NOT TARGET ${LIBRARY_NAME})
    add_custom_target(
      ${LIBRARY_NAME}
      ALL
      DEPENDS ${lib_file}
    )

    set_target_properties(
      ${LIBRARY_NAME}
      PROPERTIES
      OUTPUT_NAME "${lib_file}"
    )
  endif(NOT TARGET ${LIBRARY_NAME})

endfunction(add_avr_library)
]]
