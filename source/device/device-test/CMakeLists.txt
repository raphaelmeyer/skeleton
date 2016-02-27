
add_executable(device-test
  device.cc
  )
add_executable(test::device-test ALIAS device-test)

target_link_libraries(device-test
  PRIVATE test::gmock-main
  PRIVATE device::device
  )

set_property(TARGET device-test PROPERTY CXX_STANDARD 14)
set_property(TARGET device-test PROPERTY CXX_STANDARD_REQUIRED ON)
