#include <gmock/gmock.h>

#include <application/doorbell.h>
#include <application/ipoll.h>
#include <application/gpio.h>

#include <condition_variable>

using namespace testing;

namespace {

class PollStub : public Module::IPoll {
public:
  PollStub()
    : _condition()
    , _mutex()
    , _result(false)
    , _ready(false)
    , _setup(false)
    , _gpio(0)
  {
  }

  virtual void setup(Module::Gpio::Path const & gpio) override final {
    _gpio = gpio.number();
    _setup = true;
  }

  virtual bool poll() override final {
    std::unique_lock<std::mutex> wait_lock(_mutex);
    _condition.wait(wait_lock, [&]{ return _ready; });
    _ready = false;
    return _result;
  }

  bool is_set_up() const {
    return _setup;
  }

  uint32_t configured_gpio() const {
    return _gpio;
  }

  void trigger(bool result) {
    std::lock_guard<std::mutex> lock(_mutex);
    _result = result;
    _ready = true;
    _condition.notify_all();
  }

private:
  std::condition_variable _condition;
  std::mutex _mutex;
  bool _result;
  bool _ready;
  bool _setup;
  uint32_t _gpio;
};

class SubscriberStub : public Module::ISubscriber {
public:
  SubscriberStub()
    : _condition()
    , _mutex()
    , _notified(false)
  {
  }

  virtual void notify() override final {
    std::lock_guard<std::mutex> lock(_mutex);
    _notified = true;
    _condition.notify_all();
  }

  bool notified_in(std::chrono::milliseconds const & milliseconds) {
    std::unique_lock<std::mutex> lock(_mutex);
    bool const notified = _condition.wait_for(lock, milliseconds, [&]{ return _notified; });
    _notified = false;
    return notified;
  }

private:
  std::condition_variable _condition;
  std::mutex _mutex;
  bool _notified;
};

using namespace std::literals::chrono_literals;

class The_doorbell : public Test {
protected:
  The_doorbell()
    : poll()
    , testee(poll)
  {
  }

  virtual void SetUp() override final {

  }

  virtual void TearDown() override final {
    testee.stop();
    poll.trigger(false);
  }

  PollStub poll;
  Module::Doorbell testee;
};

TEST_F(The_doorbell, sets_up_the_gpio_for_polling_on_start)
{
  testee.start();

  // work around
  std::this_thread::sleep_for(10ms);

  ASSERT_TRUE(poll.is_set_up());
}

TEST_F(The_doorbell, configures_gpio_17_for_polling)
{
  testee.start();

  ASSERT_THAT(poll.configured_gpio(), Eq(17));

  std::this_thread::sleep_for(10ms);
}

TEST_F(The_doorbell, notifies_the_subscribers_when_the_button_is_pushed)
{
  SubscriberStub subscriber;

  testee.start();
  testee.subscribe(subscriber);

  poll.trigger(true);

  ASSERT_TRUE(subscriber.notified_in(10ms));
}

TEST_F(The_doorbell, does_not_notify_the_subscribers_on_a_spurious_wakeup)
{
  SubscriberStub subscriber;

  testee.start();
  testee.subscribe(subscriber);

  poll.trigger(false);

  ASSERT_FALSE(subscriber.notified_in(10ms));
}

TEST_F(The_doorbell, notifies_all_subscribers)
{
  SubscriberStub subscriber;
  SubscriberStub another_subscriber;

  testee.start();
  testee.subscribe(subscriber);
  testee.subscribe(another_subscriber);

  poll.trigger(true);

  ASSERT_TRUE(subscriber.notified_in(10ms));
  ASSERT_TRUE(another_subscriber.notified_in(10ms));
  testee.stop();
  poll.trigger(false);
}

TEST_F(The_doorbell, notifies_the_subscribers_on_each_interrupt)
{
  SubscriberStub subscriber;

  testee.start();
  testee.subscribe(subscriber);

  poll.trigger(true);
  ASSERT_TRUE(subscriber.notified_in(10ms));

  poll.trigger(true);
  ASSERT_TRUE(subscriber.notified_in(10ms));
}

}
