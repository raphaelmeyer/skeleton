########################################################################
cmake_minimum_required(VERSION 3.2)
########################################################################

project (skeleton VERSION 0.0.1)

########################################################################

include(googletest.cmake)
include(cucumber-cpp.cmake)

########################################################################

add_subdirectory(module)
add_subdirectory(device)

########################################################################

enable_testing()
add_test(NAME run-application-test COMMAND test::application-test)
add_test(NAME run-device-test COMMAND test::device-test)
