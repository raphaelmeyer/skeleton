#include <gmock/gmock.h>

#include <application/doorbell.h>

#include "poll_stub.h"
#include "subscriber_stub.h"

using namespace testing;

namespace {

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

  Stub::Poll poll;
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
  Stub::Subscriber subscriber;

  testee.start();
  testee.subscribe(subscriber);

  poll.trigger(true);

  ASSERT_TRUE(subscriber.notified_in(10ms));
}

TEST_F(The_doorbell, does_not_notify_the_subscribers_on_a_spurious_wakeup)
{
  Stub::Subscriber subscriber;

  testee.start();
  testee.subscribe(subscriber);

  poll.trigger(false);

  ASSERT_FALSE(subscriber.notified_in(10ms));
}

TEST_F(The_doorbell, notifies_all_subscribers)
{
  Stub::Subscriber subscriber;
  Stub::Subscriber another_subscriber;

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
  Stub::Subscriber subscriber;

  testee.start();
  testee.subscribe(subscriber);

  poll.trigger(true);
  ASSERT_TRUE(subscriber.notified_in(10ms));

  poll.trigger(true);
  ASSERT_TRUE(subscriber.notified_in(10ms));
}

}
