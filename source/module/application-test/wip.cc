#include <gmock/gmock.h>

#include <application/controller.h>
#include <application/scheduler.h>

#include "command_mock.h"
#include "scheduler_mock.h"

using namespace testing;

namespace {

TEST(The_picture, DISABLED_shall_not_be_upside_down) {
  StrictMock<Mock::Command> shell;
  Module::Scheduler scheduler;
  Module::Controller testee(shell, scheduler);

  EXPECT_CALL(shell, execute(AllOf(HasSubstr("-hf"), HasSubstr("-vf"))));

  testee.notify();
}

}

