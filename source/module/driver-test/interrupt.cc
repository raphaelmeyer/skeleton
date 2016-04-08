#include <gmock/gmock.h>

#include <application/poll.h>
#include <application/gpio.h>

#include <fstream>
#include <future>

using namespace testing;

namespace
{

TEST(The_interrupt_polling, blocks_until_a_rising_edge_occurs)
{
  std::ofstream enable("/sys/class/gpio/export");
  enable << "5";
  enable.close();

  std::ofstream direction("/sys/class/gpio/gpio5/direction");
  direction << "out";
  direction.close();

  std::ofstream value("/sys/class/gpio/gpio5/value");
  value << "0" << std::flush;

  Module::Gpio::Path gpio(26);
  Module::Poll poll;
  poll.setup(gpio);

  auto interrupted = std::async(std::launch::async, [&]{
    return poll.poll();
  });

  using namespace std::literals::chrono_literals;

  ASSERT_THAT(interrupted.wait_for(500ms), Eq(std::future_status::timeout));

  value << "1" << std::flush;
  std::this_thread::sleep_for(20ms);
  value << "0" << std::flush;

  ASSERT_THAT(interrupted.wait_for(500ms), Eq(std::future_status::ready));
  ASSERT_TRUE(interrupted.get());
}

}
