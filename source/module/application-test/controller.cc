#include <gmock/gmock.h>

#include <application/controller.h>
#include <application/scheduler.h>
#include <application/icommand.h>

using namespace testing;

namespace {

class CommandMock : public Module::ICommand {
public:
  MOCK_METHOD1(execute, void(std::string const & command));
};

class SchedulerMock : public Module::IScheduler {
public:
  virtual std::future<void> schedule(std::function<void()> request) {
    schedule_proxy(request);
    std::promise<void> promise;
    promise.set_value();
    return promise.get_future();
  }

  MOCK_METHOD1(schedule_proxy, void(std::function<void()> request));
};

TEST(The_controller, uses_a_scheduler_for_handling_a_notification)
{
  NiceMock<CommandMock> shell;
  SchedulerMock scheduler;
  Module::Controller testee(shell, scheduler);

  EXPECT_CALL(scheduler, schedule_proxy(_));

  testee.notify();
}

TEST(The_controller, takes_a_picture_when_notified_by_the_doorbell)
{
  StrictMock<CommandMock> shell;
  Module::Scheduler scheduler;
  Module::Controller testee(shell, scheduler);

  EXPECT_CALL(shell, execute(StartsWith("raspistill")));

  testee.notify();
}


}
