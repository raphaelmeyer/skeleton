cmake_minimum_required(VERSION 3.0)

project (skeleton VERSION 0.0.1)

########################################################################

add_subdirectory(gmock-1.7.0)
add_subdirectory(cucumber-cpp-0.3)

########################################################################

add_definitions(
  -std=c++14
  )

add_library(app
  app/application.cc
  )
add_library(ws::app ALIAS app)

target_include_directories(app
  PUBLIC app/inc
  )

set_property(TARGET app PROPERTY CXX_STANDARD 14)
set_property(TARGET app PROPERTY CXX_STANDARD_REQUIRED ON)

########################################################################

add_subdirectory(app-test)
add_subdirectory(acceptance-test-host)

########################################################################

enable_testing()
add_test(NAME run-app-test COMMAND ws::app-test)

########################################################################

add_executable(skeleton
  main/main.cc
  )
add_executable(ws::skeleton ALIAS skeleton)

target_link_libraries(skeleton
  PRIVATE ws::app
  )

