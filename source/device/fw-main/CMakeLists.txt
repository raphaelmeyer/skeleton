########################################################################
# TODO move into include file
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

########################################################################

add_avr_executable(fw-main
  main.cc
  )
########################################################################
# TODO add_executable(device::fw-main ALIAS fw-main)
########################################################################

set_property(TARGET fw-main PROPERTY CXX_STANDARD 11)
set_property(TARGET fw-main PROPERTY CXX_STANDARD_REQUIRED ON)

set_property(TARGET fw-main PROPERTY C_STANDARD 11)
set_property(TARGET fw-main PROPERTY C_STANDARD_REQUIRED ON)
