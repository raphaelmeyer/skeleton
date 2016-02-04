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
