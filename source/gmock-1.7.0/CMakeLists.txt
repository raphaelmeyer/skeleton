project(gmock VERSION 1.7.0)

add_library(gmock
  gmock-gtest-all.cc
  )
add_library(ws::gmock ALIAS gmock)

target_include_directories(gmock
  PUBLIC include
  )

add_library(gmock-main
  gmock_main.cc
  )
add_library(ws::gmock-main ALIAS gmock-main)

target_link_libraries(gmock-main
  PRIVATE ws::gmock
  )

