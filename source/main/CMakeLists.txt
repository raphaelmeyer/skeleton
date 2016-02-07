add_executable(skeleton
  main.cc
  )
add_executable(controller::skeleton ALIAS skeleton)

target_link_libraries(skeleton
  PRIVATE controller::app
  )

set_property(TARGET skeleton PROPERTY CXX_STANDARD 14)
