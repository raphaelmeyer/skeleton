
add_executable(acceptance-test-host
  main.cc
  )
add_executable(test::acceptance-test-host ALIAS acceptance-test-host)

target_link_libraries(acceptance-test-host
  PRIVATE test::cucumber-cpp
  )

set_property(TARGET acceptance-test-host PROPERTY CXX_STANDARD 14)
set_property(TARGET acceptance-test-host PROPERTY CXX_STANDARD_REQUIRED ON)
