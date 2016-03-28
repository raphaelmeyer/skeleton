
add_library(application
  application.cc
  include/application/application.h
  include/application/icommand.h
  include/application/iinterrupt.h
  )
add_library(controller::application ALIAS application)

target_include_directories(application
  PUBLIC include
  )

set_property(TARGET application PROPERTY CXX_STANDARD 14)
set_property(TARGET application PROPERTY CXX_STANDARD_REQUIRED ON)
