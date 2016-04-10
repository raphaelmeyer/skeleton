
add_executable(module-exe
  main.cc
  )
add_executable(module::module-exe ALIAS module-exe)

target_link_libraries(module-exe
  PRIVATE module::application
  PRIVATE pthread
  )

set_property(TARGET module-exe PROPERTY CXX_STANDARD 14)
set_property(TARGET module-exe PROPERTY CXX_STANDARD_REQUIRED ON)
