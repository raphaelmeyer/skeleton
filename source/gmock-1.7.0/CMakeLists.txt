########################################################################
project(gmock VERSION 1.7.0)
########################################################################

add_library(gmock
  gmock-gtest-all.cc
  )
add_library(test::gmock ALIAS gmock)

target_include_directories(gmock
  PUBLIC include
  )

set_property(TARGET gmock PROPERTY CXX_STANDARD 14)
set_property(TARGET gmock PROPERTY CXX_STANDARD_REQUIRED ON)

########################################################################

add_library(gmock-main
  gmock_main.cc
  )
add_library(test::gmock-main ALIAS gmock-main)

target_link_libraries(gmock-main
  PUBLIC test::gmock
  PRIVATE pthread
  )

set_property(TARGET gmock-main PROPERTY CXX_STANDARD 14)
set_property(TARGET gmock-main PROPERTY CXX_STANDARD_REQUIRED ON)
