#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cucumber-cpp/defs.hpp>

#include "controller_context.h"

namespace {

using cucumber::ScenarioScope;
using namespace testing;

GIVEN("^the internet module is connected to a doorbell$") {
}

WHEN("^the doorbell rings$") {
  ScenarioScope<ControllerContext> context;
  context->bell_interrupt().pulse();
}

THEN("^the internet module takes a picture$") {
  ScenarioScope<ControllerContext> context;
  ASSERT_THAT(context->commands().list(), SizeIs(1));
  ASSERT_THAT(context->commands().list(), Contains("raspistill -o picture.jpg"));
}

} // namespace
