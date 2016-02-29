#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cucumber-cpp/defs.hpp>

#include "device_context.h"

uint8_t volatile PINB;
uint8_t volatile PORTB;
uint8_t volatile DDRB;

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

  THEN("^the doorbell rings$") {
    ScenarioScope<DeviceContext> context;
    PwmSpy & bell = context->bell();
    ASSERT_THAT(bell.events(), SizeIs(1));
  }

}
