#include <gmock/gmock.h>

#include <application/application.h>

#include <application/icommand.h>
#include <application/iinterrupt.h>

#include <thread>
#include <condition_variable>

using namespace ::testing;

namespace Stub {

class Interrupt : public Controller::IInterrupt
{
public:
  virtual void subscribe(Controller::ISubscriber & subscriber) {}

  void pulse() {}
};

} // namespace Stub

namespace Mock {

class Command : public Controller::ICommand
{
public:
  MOCK_METHOD1(execute, void(std::string const &command));
};

} // namespace Mock

namespace {

TEST(The_application, DISABLED_shall_shutdown_within_10_milliseconds)
{
  using namespace std::chrono_literals;

  Controller::Application application;

  std::condition_variable stopped;
  std::thread application_thread([&]{
    application.run();
    stopped.notify_all();
  });

  application.shutdown();

  std::mutex mutex;
  std::unique_lock<std::mutex> lock(mutex);
  ASSERT_THAT(stopped.wait_for(lock, 10ms), Eq(std::cv_status::no_timeout));
}

TEST(The_application, DISABLED_does_not_shutdown_until_asked_for)
{
  using namespace std::chrono_literals;

  Controller::Application application;

  std::condition_variable stopped;

  std::thread application_thread([&]{
    application.run();
    stopped.notify_all();
  });

  std::mutex mutex;
  std::unique_lock<std::mutex> lock(mutex);
  ASSERT_THAT(stopped.wait_for(lock, 100ms), Eq(std::cv_status::timeout));

  application.shutdown();
  stopped.wait(lock);
}

TEST(The_application, DISABLED_takes_a_picture_when_the_doorbell_rings)
{
  Stub::Interrupt doorbell_signal;
  Mock::Command shell_command;

  Controller::Application application;

  EXPECT_CALL(shell_command, execute(StartsWith("raspistill")));

  // run application -> fixture?

  doorbell_signal.pulse();

  // shutdown application -> fixture?
}

}
