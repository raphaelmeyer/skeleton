cmake_minimum_required(VERSION 3.0)

project(Cucumber-Cpp VERSION 0.3)

add_library(cucumber-cpp
  src/ContextManager.cpp
  src/CukeCommands.cpp
  src/CukeEngine.cpp
  src/CukeEngineImpl.cpp
  src/HookRegistrar.cpp
  src/main.cpp
  src/Regex.cpp
  src/Scenario.cpp
  src/StepManager.cpp
  src/Table.cpp
  src/Tag.cpp
  src/connectors/wire/WireServer.cpp
  src/connectors/wire/WireProtocol.cpp
  src/connectors/wire/WireProtocolCommands.cpp
  src/drivers/GTestDriver.cpp
  )
add_library(ws::cucumber-cpp ALIAS cucumber-cpp)

target_include_directories(cucumber-cpp
  PUBLIC include
  )

target_link_libraries(cucumber-cpp
  PRIVATE ws::gmock
  )

#set(CUKE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
#include_directories(${CUKE_INCLUDE_DIR})

#add_subdirectory(src)
#add_subdirectory(tests)

