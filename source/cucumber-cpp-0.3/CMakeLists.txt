cmake_minimum_required(VERSION 3.0)

project(Cucumber-Cpp VERSION 0.3)

add_library(cucumber-cpp)
add_library(ws::cucumber-cpp ALIAS cucumber-cpp)

target_link_libraries(cucumber-cpp
  PRIVATE ws::gmock
  )

#set(CUKE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
#include_directories(${CUKE_INCLUDE_DIR})

#add_subdirectory(src)
#add_subdirectory(tests)

