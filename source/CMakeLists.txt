########################################################################
cmake_minimum_required(VERSION 3.2)
########################################################################

project (skeleton VERSION 0.0.1)

########################################################################

add_subdirectory(cucumber-cpp-0.3)
add_subdirectory(gmock-1.7.0)

########################################################################

add_subdirectory(controller)
add_subdirectory(device)

########################################################################

enable_testing()
add_test(NAME run-application-test COMMAND test::application-test)
add_test(NAME run-device-test COMMAND test::device-test)
