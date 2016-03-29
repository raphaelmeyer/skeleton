#include <gmock/gmock.h>

#include <application/controller.h>
#include <application/icommand.h>

using namespace testing;

namespace {

class CommandMock : public Module::ICommand {
public:
  MOCK_METHOD1(execute, void(std::string const & command));
};

/*
class IRequest;
class IResponse;

class IScheduler
{
public:
  std::unique_ptr<IResponse> schedule(std::unique_ptr<IRequest> request) = 0;
};
*/

TEST(The_controller, DISABLED_uses_a_scheduler_handle_a_notification)
{
  /*
  CommandMock shell;
  SchedulerMock scheduler;
  Controller testee(shell, scheduler);

  EXPECT_CALL(scheduler, schedule(_))
    .WillOnce(Return());
  */
}

TEST(The_controller, takes_a_picture_when_notified_by_the_doorbell)
{
  StrictMock<CommandMock> shell;
  //Scheduler scheduler;
  Module::Controller testee(shell);

  EXPECT_CALL(shell, execute(StartsWith("raspistill")));

  testee.notify();
}


}
