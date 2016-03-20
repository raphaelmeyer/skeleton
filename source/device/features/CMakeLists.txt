
add_executable(device-cucumber
  step_definitions/steps.cc
  test_doubles/seams.cc
  test_doubles/seams_interrupt.cc
  step_definitions/device_context.h
  test_doubles/gpio_stub.h
  test_doubles/pwm_spy.h
  )
add_executable(test::device-cucumber ALIAS device-cucumber)

target_include_directories(device-cucumber
  PRIVATE test_doubles
  )

target_link_libraries(device-cucumber
  PRIVATE device::device
  PRIVATE test::cucumber-cpp
  )

set_property(TARGET device-cucumber PROPERTY CXX_STANDARD 14)
set_property(TARGET device-cucumber PROPERTY CXX_STANDARD_REQUIRED ON)
