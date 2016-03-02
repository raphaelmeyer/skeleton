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
    ScenarioScope<DeviceContext> context;
    PwmSpy & bell = context->bell();
    ASSERT_THAT(bell.events(), SizeIs(2));
    ASSERT_THAT(bell.events().at(0).name, StrEq("on"));
    ASSERT_THAT(bell.events().at(1).name, StrEq("off"));
    //duration = bell.events().at(0).time - bell.events().at(1).time
    //ASSERT_THAT(duration, InRange(ms * .9, ms * 1.1));
  }

}
