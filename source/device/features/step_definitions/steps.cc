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

WHEN("^I press the doorbell button$") {
  ScenarioScope<DeviceContext> context;
  context->press_button();
}

THEN("^the doorbell rings for about (\\d+) ms$") {
  REGEX_PARAM(uint32_t, milliseconds);
  ScenarioScope<DeviceContext> context;
  Spy::Pwm & bell = context->bell();

  uint32_t const tolerance = milliseconds / 10;
  uint32_t const ringing = context->now() + tolerance;
  uint32_t const still_ringing = context->now() + milliseconds - tolerance;
  uint32_t const ringing_ended = context->now() + milliseconds + tolerance;

  context->advance_until(ringing);
  ASSERT_THAT(bell.events(), SizeIs(1));
  ASSERT_THAT(bell.events().at(0).name, StrEq("on"));

  context->advance_until(still_ringing);
  ASSERT_THAT(bell.events(), SizeIs(1));

  context->advance_until(ringing_ended);
  ASSERT_THAT(bell.events(), SizeIs(2));
  ASSERT_THAT(bell.events().at(1).name, StrEq("off"));
}

THEN("^the doorbell notifies the internet module$")
{
  ScenarioScope<DeviceContext> context;

  context->advance(10);
  ASSERT_TRUE(context->notify_pin().is_high());

  context->advance(20);
  ASSERT_FALSE(context->notify_pin().is_high());
}

}
