#include <gmock/gmock.h>

#include <application/controller.h>

using namespace testing;

namespace {

class IRequest;
class IResponse;

class IScheduler
{
public:
  std::unique_ptr<IResponse> schedule(std::unique_ptr<IRequest> request) = 0;
};

TEST(The_controller, DISABLED_uses_a_scheduler_handle_a_notification)
{
  /*
  CommandMock shell;
  SchedulerMock scheduler;
  Controller controller(shell, scheduler);

  EXPECT_CALL(scheduler, schedule(_))
    .WillOnce(Return());
  */
}

TEST(The_controller, DISABLED_takes_a_picture_when_notified_by_the_doorbell)
{
  /*
  CommandMock shell;
  Scheduler scheduler;
  Controller controller(shell, scheduler);

  EXPECT_CALL(shell, execute(StartsWith("raspistill")));

  controller.notify();
  */
}


}
