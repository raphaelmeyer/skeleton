#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cucumber-cpp/defs.hpp>

#include "device_context.h"

namespace
{
  using cucumber::ScenarioScope;
  using namespace ::testing;

  BEFORE()
  {
    ScenarioScope<DeviceContext> context;
    context->start();
  }

  AFTER()
  {
    ScenarioScope<DeviceContext> context;
    context->stop();
  }

  GIVEN("^I press the doorbell button$") {
    ScenarioScope<DeviceContext> context;
    context->button().press();
  }

  THEN("^the doorbell rings for about (\\d+) ms$") {
    REGEX_PARAM(uint32_t, milliseconds);
    ScenarioScope<DeviceContext> context;
    Spy::Pwm & bell = context->bell();

    ASSERT_THAT(bell.events(), SizeIs(1));
    ASSERT_THAT(bell.events().at(0).name, StrEq("on"));

    context->advance(milliseconds - 1);
    ASSERT_THAT(bell.events(), SizeIs(1));

    context->advance(milliseconds - 1);
    ASSERT_THAT(bell.events(), SizeIs(2));
    ASSERT_THAT(bell.events().at(1).name, StrEq("off"));
  }

}
