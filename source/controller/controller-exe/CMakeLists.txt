########################################################################
# Workaround for cmake 3.0
add_definitions(-std=c++14)
########################################################################


add_executable(controller-exe
  main.cc
  )
add_executable(controller::controller-exe ALIAS controller-exe)

target_link_libraries(controller-exe
  PRIVATE controller::application
  )

set_property(TARGET controller-exe PROPERTY CXX_STANDARD 14)
set_property(TARGET controller-exe PROPERTY CXX_STANDARD_REQUIRED ON)
