#include <gmock/gmock.h>

#include <application/controller.h>
#include <application/scheduler.h>

#include "command_mock.h"
#include "scheduler_mock.h"

using namespace testing;

namespace {

TEST(The_controller, uses_a_scheduler_for_handling_a_notification)
{
  NiceMock<Mock::Command> shell;
  Mock::Scheduler scheduler;
  Module::Controller testee(shell, scheduler);

  EXPECT_CALL(scheduler, schedule_proxy(_));

  testee.notify();
}

TEST(The_controller, takes_a_picture_when_notified_by_the_doorbell)
{
  StrictMock<Mock::Command> shell;
  Module::Scheduler scheduler;
  Module::Controller testee(shell, scheduler);

  EXPECT_CALL(shell, execute(StartsWith("raspistill")));

  testee.notify();
}


}
