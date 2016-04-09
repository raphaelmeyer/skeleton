#include <gmock/gmock.h>

#include <application/application.h>

#include "command_mock.h"
#include "interrupt_stub.h"

#include <thread>
#include <future>

using namespace testing;
using namespace std::literals::chrono_literals;

namespace {

TEST(The_application, shall_shutdown_within_10_milliseconds)
{
  Stub::Interrupt doorbell;
  Mock::Command shell;

  Module::Application testee(doorbell, shell);
  testee.init();

  auto shutdown = std::async(std::launch::async, []{
    testee.run();
  });

  testee.shutdown();

  ASSERT_THAT(shutdown.wait_for(10ms), Eq(std::future_status::ready));
  shutdown.get();
}

TEST(The_application, takes_a_picture_when_the_doorbell_rings)
{
  Stub::Interrupt doorbell;
  StrictMock<Mock::Command> shell;

  Module::Application testee(doorbell, shell);
  testee.init();

  std::thread application_thread([&]{
    testee.run();
  });

  EXPECT_CALL(shell, execute(StartsWith("raspistill")));

  doorbell.pulse();

  testee.shutdown();
  application_thread.join();
}

}
