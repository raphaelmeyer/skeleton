
add_executable(acceptance-test-host
  main.cc
  )
add_executable(ws::acceptance-test-host ALIAS acceptance-test-host)

target_link_libraries(acceptance-test-host
  PRIVATE ws::cucumber-cpp
  )

