#include <gmock/gmock.h>

#include <application/application.h>

#include <application/icommand.h>
#include <application/iinterrupt.h>

#include <thread>

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

TEST(The_application, shall_shutdown_within_10_milliseconds)
{
  using namespace std::chrono_literals;

  Controller::Application application;

  std::mutex mutex;
  std::condition_variable condition;
  bool stopped = false;

  std::thread application_thread([&]{
    application.run();
    {
      std::lock_guard<std::mutex> lock(mutex);
      stopped = true;
    }
    condition.notify_all();
  });

  application.shutdown();

  std::unique_lock<std::mutex> lock(mutex);
  ASSERT_TRUE(condition.wait_for(lock, 10ms, [&]{ return stopped; }));

  application_thread.join();
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
