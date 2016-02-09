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
