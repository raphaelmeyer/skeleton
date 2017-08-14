
add_executable(driver-test
  interrupt.cc
  )
add_executable(test::driver-test ALIAS driver-test)

target_link_libraries(driver-test
  PRIVATE test::googlemock-main
  PRIVATE module::application
  )

set_property(TARGET driver-test PROPERTY CXX_STANDARD 14)
set_property(TARGET driver-test PROPERTY CXX_STANDARD_REQUIRED ON)
