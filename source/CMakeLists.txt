########################################################################
# TODO cmake_minimum_required(VERSION 3.2)
cmake_minimum_required(VERSION 3.0)
########################################################################

project (skeleton VERSION 0.0.1)

########################################################################

add_subdirectory(cucumber-cpp-0.3)
add_subdirectory(gmock-1.7.0)

########################################################################

add_subdirectory(fw)
add_subdirectory(fw-test)
add_subdirectory(fw-main)

########################################################################

add_subdirectory(main)
add_subdirectory(app)
add_subdirectory(app-test)
add_subdirectory(acceptance-test-host)

########################################################################

enable_testing()
add_test(NAME run-app-test COMMAND test::app-test)

########################################################################


