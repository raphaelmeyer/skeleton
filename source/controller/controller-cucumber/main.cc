#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cucumber-cpp/defs.hpp>

namespace {

  using cucumber::ScenarioScope;
  using namespace ::testing;

  struct AppContext {
  };

  GIVEN("^something$") {
    ASSERT_THAT(1 + 2, Eq(3));
  }

  WHEN("^I do something$") {
    FAIL();
  }

  THEN("^there will be something$") {
    pending();
  }

}

