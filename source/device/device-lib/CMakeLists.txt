set(SOURCE_FILES
  device.c
  include/device/device.h
  )

add_library(device
  ${SOURCE_FILES}
  )
add_library(device::device ALIAS device)

target_include_directories(device
  PUBLIC include
  )

set_avr_library_properties(device)

set_property(TARGET device PROPERTY C_STANDARD 11)
set_property(TARGET device PROPERTY C_STANDARD_REQUIRED ON)
