
add_executable(controller-exe
  main.cc
  )
add_executable(controller::controller-exe ALIAS controller-exe)

target_link_libraries(controller-exe
  PRIVATE controller::application
  )

set_property(TARGET controller-exe PROPERTY CXX_STANDARD 14)
