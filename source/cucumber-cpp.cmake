find_package(Threads)

add_library(cucumber-cpp
  cucumber-cpp/src/ContextManager.cpp
  cucumber-cpp/src/CukeCommands.cpp
  cucumber-cpp/src/CukeEngine.cpp
  cucumber-cpp/src/CukeEngineImpl.cpp
  cucumber-cpp/src/HookRegistrar.cpp
  cucumber-cpp/src/main.cpp
  cucumber-cpp/src/Regex.cpp
  cucumber-cpp/src/Scenario.cpp
  cucumber-cpp/src/StepManager.cpp
  cucumber-cpp/src/Table.cpp
  cucumber-cpp/src/Tag.cpp
  cucumber-cpp/src/connectors/wire/WireServer.cpp
  cucumber-cpp/src/connectors/wire/WireProtocol.cpp
  cucumber-cpp/src/connectors/wire/WireProtocolCommands.cpp
  cucumber-cpp/src/drivers/GTestDriver.cpp
)
add_library(test::cucumber-cpp ALIAS cucumber-cpp)

target_include_directories(cucumber-cpp
  PUBLIC cucumber-cpp/include
)

target_link_libraries(cucumber-cpp
  PUBLIC test::googlemock
  PRIVATE ${CMAKE_THREAD_LIBS_INIT}
  PRIVATE boost_regex boost_system boost_program_options boost_filesystem
)

set_property(TARGET cucumber-cpp PROPERTY CXX_STANDARD 14)
set_property(TARGET cucumber-cpp PROPERTY CXX_STANDARD_REQUIRED ON)

