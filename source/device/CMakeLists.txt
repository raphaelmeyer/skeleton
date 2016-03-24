########################################################################
include(avr.cmake)
########################################################################

add_subdirectory(device-exe)

add_subdirectory(features)

add_subdirectory(device-test)
add_subdirectory(device-lib)
