#include <gmock/gmock.h>

#include <application/poll.h>
#include <application/gpio.h>

#include <fstream>
#include <future>

using namespace testing;
using namespace std::literals::chrono_literals;

namespace
{

class The_interrupt_polling : public Test {
protected:
  The_interrupt_polling()
  : interrupted()
  , gpio(26)
  , poll()
  {
  }

  virtual void SetUp() override final {
    std::ofstream enable("/sys/class/gpio/export");
    enable << "5";
    enable.close();

    std::ofstream direction("/sys/class/gpio/gpio5/direction");
    direction << "out";
    direction.close();

    std::ofstream value("/sys/class/gpio/gpio5/value");
    value << "0" << std::flush;
  }

  Module::Gpio::Path gpio;
  Module::Poll poll;
  std::future<bool> interrupted;
};

TEST_F(The_interrupt_polling, blocks_until_a_rising_edge_occurs)
{
  poll.setup(gpio);

  std::promise<bool> poll_result;
  interrupted = poll_result.get_future();

  std::thread poll_thread([&]{
    bool const result = poll.poll();
    poll_result.set_value(result);
  });

  ASSERT_THAT(interrupted.wait_for(500ms), Eq(std::future_status::timeout));

  std::ofstream value("/sys/class/gpio/gpio5/value");
  value << "1" << std::flush;
  std::this_thread::sleep_for(20ms);
  value << "0" << std::flush;

  ASSERT_THAT(interrupted.wait_for(500ms), Eq(std::future_status::ready));
  ASSERT_TRUE(interrupted.get());

  poll_thread.join();
}

TEST_F(The_interrupt_polling, catches_a_rising_edge_that_occured_before_polling)
{
  poll.setup(gpio);

  std::ofstream value("/sys/class/gpio/gpio5/value");
  value << "1" << std::flush;
  std::this_thread::sleep_for(20ms);
  value << "0" << std::flush;

  std::promise<bool> poll_result;
  interrupted = poll_result.get_future();

  std::thread poll_thread([&]{
    bool const result = poll.poll();
    poll_result.set_value(result);
  });

  ASSERT_THAT(interrupted.wait_for(500ms), Eq(std::future_status::ready));
  ASSERT_TRUE(interrupted.get());

  poll_thread.join();
}

TEST_F(The_interrupt_polling, clears_interrupts_on_setup)
{
  std::ofstream value("/sys/class/gpio/gpio5/value");
  value << "1" << std::flush;
  std::this_thread::sleep_for(20ms);
  value << "0" << std::flush;

  poll.setup(gpio);

  std::promise<bool> poll_result;
  interrupted = poll_result.get_future();

  std::thread poll_thread([&]{
    bool const result = poll.poll();
    poll_result.set_value(result);
  });

  ASSERT_THAT(interrupted.wait_for(500ms), Eq(std::future_status::timeout));

  // tear down

  value << "1" << std::flush;
  std::this_thread::sleep_for(20ms);
  value << "0" << std::flush;

  ASSERT_THAT(interrupted.wait_for(500ms), Eq(std::future_status::ready));
  ASSERT_TRUE(interrupted.get());

  poll_thread.join();
}

}
