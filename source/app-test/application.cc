#include <gmock/gmock.h>

#include <app/application.h>

using namespace ::testing;

TEST(a_dummy_test, that_fails) {
  WS::Application app;
  FAIL();
}

