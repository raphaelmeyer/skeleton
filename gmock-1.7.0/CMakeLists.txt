project(gmock VERSION 1.7.0)

add_library(gmock
  gmock-gtest-all.cc
)

add_library(ws::gmock ALIAS gmock)

