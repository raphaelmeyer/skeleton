#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cucumber-cpp/defs.hpp>

#include "device_context.h"

using namespace std::chrono_literals;

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
    ScenarioScope<DeviceContext> context;
    Spy::Pwm & bell = context->bell();
    Stub::Timer & timer = context->timer();

    ASSERT_THAT(bell.events(), SizeIs(1));
    ASSERT_THAT(bell.events().at(0).name, StrEq("on"));

    ASSERT_THAT(timer.events(), SizeIs(1));
    ASSERT_THAT(timer.events().at(0), StrEq("start"));

    // TODO: ASSERT_THAT(timer.set_for(), Eq(...ms));

    timer.expire();
    context->run_for(10ms);

    ASSERT_THAT(bell.events(), SizeIs(2));
    ASSERT_THAT(bell.events().at(1).name, StrEq("off"));
  }

}
