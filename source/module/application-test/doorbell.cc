#include <gmock/gmock.h>

#include <application/doorbell.h>
#include <application/ipoll.h>

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
  {
  }

  void setup(Module::Gpio::Path & path) {
  }

  bool poll() {
    std::unique_lock<std::mutex> wait_lock(_mutex);
    _condition.wait(wait_lock, [&]{ return _ready; });

    _ready = false;
    return _result;
  }

  void trigger(bool result) {
    {
      std::lock_guard<std::mutex> lock(_mutex);
      _result = result;
      _ready = true;
    }
    _condition.notify_all();
  }

private:
  std::condition_variable _condition;
  std::mutex _mutex;
  bool _result;
  bool _ready;
};

class SubscriberMock : public Module::ISubscriber {
public:
  MOCK_METHOD0(notify, void());
};

TEST(The_doorbell, notifies_the_subscribers_when_the_button_is_pushed)
{
  PollStub button;
  StrictMock<SubscriberMock> subscriber;

  EXPECT_CALL(subscriber, notify())
    .Times(1);

  Module::Doorbell testee(button);

  testee.start();
  testee.subscribe(subscriber);

  button.trigger(true);
}

TEST(The_doorbell, does_not_notify_the_subscribers_on_a_spurious_wakeup)
{
  PollStub button;
  StrictMock<SubscriberMock> subscriber;

  Module::Doorbell testee(button);

  EXPECT_CALL(subscriber, notify())
    .Times(0);

  testee.start();
  testee.subscribe(subscriber);

  button.trigger(false);
}

TEST(The_doorbell, notifies_all_subscribers)
{
  PollStub button;
  StrictMock<SubscriberMock> subscriber;
  StrictMock<SubscriberMock> another_subscriber;

  Module::Doorbell testee(button);

  EXPECT_CALL(subscriber, notify())
    .Times(1);

  EXPECT_CALL(another_subscriber, notify())
    .Times(1);

  testee.start();
  testee.subscribe(subscriber);
  testee.subscribe(another_subscriber);

  button.trigger(true);
}

TEST(The_doorbell, DISABLED_notifies_subscribers_that_registered_before_starting)
{
  FAIL();
}

TEST(The_doorbell, DISABLED_notifies_subscribers_that_registered_after_starting)
{
  FAIL();
}


TEST(The_doorbell, DISABLED_notifies_the_subscribers_on_each_interrupt)
{
  FAIL();
}


}
