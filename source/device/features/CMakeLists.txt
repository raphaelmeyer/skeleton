
add_executable(device-cucumber
  step_definitions/dummy.cc
  step_definitions/steps.cc
  step_definitions/device_context.h
  step_definitions/gpio_stub.h
  step_definitions/pwm_spy.h
  step_definitions/seams.cc)
add_executable(test::device-cucumber ALIAS device-cucumber)

target_link_libraries(device-cucumber
  PRIVATE device::device
  PRIVATE test::cucumber-cpp
  )

set_property(TARGET device-cucumber PROPERTY CXX_STANDARD 14)
set_property(TARGET device-cucumber PROPERTY CXX_STANDARD_REQUIRED ON)
