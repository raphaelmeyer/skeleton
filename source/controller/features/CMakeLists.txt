
add_executable(controller-cucumber
  step_definitions/steps.cc
  step_definitions/dummy.cc
  step_definitions/controller_context.h
  )
add_executable(test::controller-cucumber ALIAS controller-cucumber)

target_link_libraries(controller-cucumber
  PRIVATE controller::application
  PRIVATE test::cucumber-cpp
  )

set_property(TARGET controller-cucumber PROPERTY CXX_STANDARD 14)
set_property(TARGET controller-cucumber PROPERTY CXX_STANDARD_REQUIRED ON)
