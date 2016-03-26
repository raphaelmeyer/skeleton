
add_executable(application-test
  application.cc
  )
add_executable(test::application-test ALIAS application-test)

target_link_libraries(application-test
  PRIVATE test::gmock-main
  PRIVATE controller::application
  )

set_property(TARGET application-test PROPERTY CXX_STANDARD 14)
set_property(TARGET application-test PROPERTY CXX_STANDARD_REQUIRED ON)

