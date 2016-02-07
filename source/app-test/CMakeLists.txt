
add_executable(app-test
  spi.cc
  )
add_executable(test::app-test ALIAS app-test)

target_link_libraries(app-test
  PRIVATE test::gmock-main
  PRIVATE controller::app
  )

set_property(TARGET app-test PROPERTY CXX_STANDARD 14)
set_property(TARGET app-test PROPERTY CXX_STANDARD_REQUIRED ON)

