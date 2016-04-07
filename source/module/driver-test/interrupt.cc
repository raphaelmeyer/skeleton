#include <gmock/gmock.h>

#include <application/poll.h>
#include <application/gpio.h>

#include <condition_variable>
#include <fstream>
#include <mutex>
#include <thread>

using namespace testing;

namespace
{

TEST(The_interrupt_polling, blocks_until_a_rising_edge_occurs)
{
  Module::Gpio::Path gpio(21);
  Module::Poll poll;

  std::ofstream enable("/sys/class/gpio/export");
  enable << "22";
  enable.close();

  std::ofstream direction("/sys/class/gpio/gpio22/direction");
  direction << "out";
  direction.close();

  std::ofstream value("/sys/class/gpio/gpio22/value");
  value << "0" << std::flush;

  std::condition_variable condition;
  std::mutex mutex;

  poll.setup(gpio);

  bool interrupted = false;

  std::thread poll_thread([&]{
    std::lock_guard<std::mutex> lock(mutex);
    interrupted = poll.poll();
  });

  std::unique_lock<std::mutex> lock(mutex);

  using namespace std::literals::chrono_literals;

  ASSERT_FALSE(condition.wait_for(lock, 500ms, [&]{ return interrupted; }));
  ASSERT_FALSE(interrupted);

  value << "1" << std::flush;
  std::this_thread::sleep_for(20ms);
  value << "0" << std::flush;

  ASSERT_TRUE(condition.wait_for(lock, 500ms, [&]{ return interrupted; }));
  ASSERT_TRUE(interrupted);

  poll_thread.join();
}

}
