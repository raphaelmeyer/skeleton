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
    // Set gpio stub to return high for a few cycles
    // Next step: bounce/chatter
    pending();
  }

  THEN("^the doorbell rings$") {
    // Check that pwm turned on once
    // Next step: Check pwm param (frequency, duration)
    pending();
  }

}
