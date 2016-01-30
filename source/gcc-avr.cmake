
##########################################################################
find_program(AVR_CC avr-gcc)
find_program(AVR_CXX avr-g++)
find_program(AVR_OBJCOPY avr-objcopy)
find_program(AVR_SIZE_TOOL avr-size)
find_program(AVR_OBJDUMP avr-objdump)

##########################################################################
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_C_COMPILER ${AVR_CC})
set(CMAKE_CXX_COMPILER ${AVR_CXX})

##########################################################################
# default MCU (chip)
if(NOT AVR_MCU)
   set(AVR_MCU atmega328p
      CACHE STRING "Set default MCU: atmega328p (see 'avr-gcc --target-help' for valid values)"
   )
endif(NOT AVR_MCU)

##########################################################################
if(NOT AVR_F_CPU)
  set(AVR_F_CPU 16000000UL
    CACHE STRING "Set default CPU frequency: 16000000UL"
    )
endif(NOT AVR_F_CPU)

##########################################################################
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

