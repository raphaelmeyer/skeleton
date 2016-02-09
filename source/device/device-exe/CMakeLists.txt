
add_executable(device-exe
  main.c
  )
add_executable(device::device-exe ALIAS device-exe)

set_avr_executable_properties(device-exe)

target_link_libraries(device-exe
  PRIVATE device::device
  )

set_property(TARGET device-exe PROPERTY C_STANDARD 11)
set_property(TARGET device-exe PROPERTY C_STANDARD_REQUIRED ON)
