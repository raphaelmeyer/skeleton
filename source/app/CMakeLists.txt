
add_library(app
  application.cc
  )
add_library(ws::app ALIAS app)

target_include_directories(app
  PUBLIC inc
  )

set_property(TARGET app PROPERTY CXX_STANDARD 14)
set_property(TARGET app PROPERTY CXX_STANDARD_REQUIRED ON)

