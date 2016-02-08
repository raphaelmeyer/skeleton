
add_executable(controller-cucumber
  main.cc
  )
add_executable(test::controller-cucumber ALIAS controller-cucumber)

target_link_libraries(controller-cucumber
  PRIVATE test::cucumber-cpp
  )

set_property(TARGET controller-cucumber PROPERTY CXX_STANDARD 14)
set_property(TARGET controller-cucumber PROPERTY CXX_STANDARD_REQUIRED ON)
