#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cucumber-cpp/defs.hpp>

#include "controller_context.h"

namespace {

using cucumber::ScenarioScope;
using namespace testing;

BEFORE()
{
  ScenarioScope<ModuleContext> context;
  context->run_application();
}

AFTER()
{
  ScenarioScope<ModuleContext> context;
  context->shutdown_application();
}

WHEN("^the doorbell rings$") {
  ScenarioScope<ModuleContext> context;
  context->doorbell().pulse();
}

THEN("^the internet module takes a picture$") {
  ScenarioScope<ModuleContext> context;
  ASSERT_THAT(context->commands(), SizeIs(1));
  ASSERT_THAT(context->commands().at(0), StartsWith("raspistill"));
}

THEN("^the picture is (\\d+) pixels wide and (\\d+) pixels high$") {
  REGEX_PARAM(std::string, width);
  REGEX_PARAM(std::string, height);

  ScenarioScope<ModuleContext> context;
  ASSERT_THAT(context->commands().back(), HasSubstr("-w " + width));
  ASSERT_THAT(context->commands().back(), HasSubstr("-h " + height));
}

} // namespace
