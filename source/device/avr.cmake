include(CMakeParseArguments)

########################################################################

function(set_avr_target_properties TARGET_NAME)
  if(CMAKE_SYSTEM_PROCESSOR STREQUAL "avr")

  cmake_parse_arguments(ARG "" "HEX" "" ${ARGN})

  if(NOT ARG_HEX)
    set(ARG_HEX ${TARGET_NAME}.hex)
  endif()

  set_target_properties(
    ${TARGET_NAME}
    PROPERTIES
    COMPILE_FLAGS "-mmcu=${AVR_MCU} -DF_CPU=${AVR_F_CPU} -Os"
    LINK_FLAGS "-mmcu=${AVR_MCU}"
  )

  add_custom_command(
    TARGET ${TARGET_NAME}
    POST_BUILD
    COMMENT "Creating hex file ${ARG_HEX}"
    COMMAND ${AVR_OBJCOPY} -O ihex -R .eeprom ${TARGET_NAME} ${ARG_HEX}
  )

  endif()
endfunction(set_avr_target_properties)

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
