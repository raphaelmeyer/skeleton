
add_executable(app-test
  application.cc
  )
add_executable(ws::app-test ALIAS app-test)

target_link_libraries(app-test
  PRIVATE ws::gmock-main
  PRIVATE ws::app
  )


