project(Cucumber-Cpp VERSION 0.3)

########################################################################
# Workaround for cmake 3.0
add_definitions(-std=c++14)
########################################################################

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
add_library(test::cucumber-cpp ALIAS cucumber-cpp)

target_include_directories(cucumber-cpp
  PUBLIC include
  )

target_link_libraries(cucumber-cpp
  PUBLIC test::gmock
  PRIVATE pthread
  PRIVATE boost_regex
  PRIVATE boost_system
  )

set_property(TARGET cucumber-cpp PROPERTY CXX_STANDARD 14)
set_property(TARGET cucumber-cpp PROPERTY CXX_STANDARD_REQUIRED ON)
