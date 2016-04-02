
add_executable(module-cucumber
  step_definitions/steps.cc
  step_definitions/controller_context.h
  )
add_executable(test::module-cucumber ALIAS module-cucumber)

target_link_libraries(module-cucumber
  PRIVATE module::application
  PRIVATE test::cucumber-cpp
  )

set_property(TARGET module-cucumber PROPERTY CXX_STANDARD 14)
set_property(TARGET module-cucumber PROPERTY CXX_STANDARD_REQUIRED ON)
