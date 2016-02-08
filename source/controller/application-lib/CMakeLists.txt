########################################################################
# Workaround for cmake 3.0
add_definitions(-std=c++14)
########################################################################

add_library(application
  application.cc
  spi.cc
  )
add_library(controller::application ALIAS application)

target_include_directories(application
  PUBLIC include
  )

set_property(TARGET application PROPERTY CXX_STANDARD 14)
set_property(TARGET application PROPERTY CXX_STANDARD_REQUIRED ON)
