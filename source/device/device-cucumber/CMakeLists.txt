
add_executable(device-cucumber
  main.cc
  device_context.h)
add_executable(test::device-cucumber ALIAS device-cucumber)

target_link_libraries(device-cucumber
  PRIVATE test::cucumber-cpp
  )

set_property(TARGET device-cucumber PROPERTY CXX_STANDARD 14)
set_property(TARGET device-cucumber PROPERTY CXX_STANDARD_REQUIRED ON)
