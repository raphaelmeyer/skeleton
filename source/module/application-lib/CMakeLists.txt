
add_library(application
  application.cc
  controller.cc
  doorbell.cc
  gpio.cc
  poll.cc
  request.cc
  scheduler.cc
  shell.cc
  include/application/application.h
  include/application/controller.h
  include/application/doorbell.h
  include/application/gpio.h
  include/application/poll.h
  include/application/request.h
  include/application/scheduler.h
  include/application/shell.h
  include/application/icommand.h
  include/application/iinterrupt.h
  include/application/irequest.h
  include/application/ischeduler.h
  )
add_library(module::application ALIAS application)

target_include_directories(application
  PUBLIC include
  )

set_property(TARGET application PROPERTY CXX_STANDARD 14)
set_property(TARGET application PROPERTY CXX_STANDARD_REQUIRED ON)
