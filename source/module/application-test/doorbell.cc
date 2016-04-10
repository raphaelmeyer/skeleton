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

TEST(The_doorbell, notifies_the_subscribers_when_the_button_is_pushed)
{
  PollStub button;
  SubscriberStub subscriber;

  Module::Doorbell testee(button);

  testee.start();
  testee.subscribe(subscriber);

  button.trigger(true);

  using namespace std::literals::chrono_literals;
  ASSERT_TRUE(subscriber.notified_in(10ms));

  testee.stop();
  button.trigger(false);
}

TEST(The_doorbell, does_not_notify_the_subscribers_on_a_spurious_wakeup)
{
  PollStub button;
  SubscriberStub subscriber;

  Module::Doorbell testee(button);

  testee.start();
  testee.subscribe(subscriber);

  button.trigger(false);

  using namespace std::literals::chrono_literals;
  ASSERT_FALSE(subscriber.notified_in(10ms));

  testee.stop();
  button.trigger(false);
}

TEST(The_doorbell, notifies_all_subscribers)
{
  PollStub button;
  SubscriberStub subscriber;
  SubscriberStub another_subscriber;

  Module::Doorbell testee(button);

  testee.start();
  testee.subscribe(subscriber);
  testee.subscribe(another_subscriber);

  button.trigger(true);

  using namespace std::literals::chrono_literals;
  ASSERT_TRUE(subscriber.notified_in(10ms));
  ASSERT_TRUE(another_subscriber.notified_in(10ms));

  testee.stop();
  button.trigger(false);
}

TEST(The_doorbell, notifies_the_subscribers_on_each_interrupt)
{
  PollStub button;
  SubscriberStub subscriber;

  Module::Doorbell testee(button);

  testee.start();
  testee.subscribe(subscriber);

  button.trigger(true);

  using namespace std::literals::chrono_literals;
  ASSERT_TRUE(subscriber.notified_in(10ms));

  button.trigger(true);

  ASSERT_TRUE(subscriber.notified_in(10ms));

  testee.stop();
  button.trigger(false);
}

}
