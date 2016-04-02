#include <gmock/gmock.h>

#include <application/application.h>

#include "command_mock.h"
#include "interrupt_stub.h"

#include <thread>

using namespace testing;
using namespace std::literals::chrono_literals;

namespace {

TEST(The_application, shall_shutdown_within_10_milliseconds)
{
  Stub::Interrupt doorbell;
  Mock::Command shell;

  Module::Application testee(doorbell, shell);

  std::mutex mutex;
  std::condition_variable condition;
  bool stopped = false;

  std::thread application_thread([&]{
    testee.run();
    {
      std::lock_guard<std::mutex> lock(mutex);
      stopped = true;
    }
    condition.notify_all();
  });

  testee.shutdown();

  std::unique_lock<std::mutex> lock(mutex);
  ASSERT_TRUE(condition.wait_for(lock, 10ms, [&]{ return stopped; }));

  application_thread.join();
}

TEST(The_application, takes_a_picture_when_the_doorbell_rings)
{
  Stub::Interrupt doorbell;
  StrictMock<Mock::Command> shell;

  Module::Application testee(doorbell, shell);

  std::thread application_thread([&]{
    testee.run();
  });

  EXPECT_CALL(shell, execute(StartsWith("raspistill")));

  doorbell.pulse();

  testee.shutdown();
  application_thread.join();
}

}
