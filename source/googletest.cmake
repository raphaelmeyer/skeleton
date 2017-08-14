find_package(Threads)

#
# googletest
#
add_library(googletest googletest/googletest/src/gtest-all.cc)
add_library(test::googletest ALIAS googletest)

target_include_directories(googletest
  PUBLIC googletest/googletest/include
  PRIVATE googletest/googletest
)

set_property(TARGET googletest PROPERTY CXX_STANDARD 14)
set_property(TARGET googletest PROPERTY CXX_STANDARD_REQUIRED ON)

#
# googlemock
#
add_library(googlemock googletest/googlemock/src/gmock-all.cc)
add_library(test::googlemock ALIAS googlemock)

target_include_directories(googlemock
  PUBLIC googletest/googlemock/include
  PRIVATE googletest/googlemock
)

target_link_libraries(googlemock googletest)

set_property(TARGET googlemock PROPERTY CXX_STANDARD 14)
set_property(TARGET googlemock PROPERTY CXX_STANDARD_REQUIRED ON)

# googlemock test runner (main)
add_library(googlemock-main googletest/googlemock/src/gmock_main.cc)
add_library(test::googlemock-main ALIAS googlemock-main)

target_link_libraries(googlemock-main
  PUBLIC googlemock
  PUBLIC ${CMAKE_THREAD_LIBS_INIT}
)

set_property(TARGET googlemock-main PROPERTY CXX_STANDARD 14)
set_property(TARGET googlemock-main PROPERTY CXX_STANDARD_REQUIRED ON)

