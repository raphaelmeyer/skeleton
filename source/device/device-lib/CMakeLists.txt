
add_library(device
  device.c
  gpio.c
  ipwm.c
  pwm.c
  system_tick.c
  timer.c
  include/device/device.h
  include/device/gpio.h
  include/device/io.h
  include/device/ipwm.h
  include/device/pwm.h
  include/device/system_tick.h
  include/device/timer.h
  seams/avr/interrupt.h
  seams/avr/io.h
  )
add_library(device::device ALIAS device)

target_include_directories(device
  PUBLIC include
  )

set_avr_library_properties(device)

set_property(TARGET device PROPERTY C_STANDARD 11)
set_property(TARGET device PROPERTY C_STANDARD_REQUIRED ON)
