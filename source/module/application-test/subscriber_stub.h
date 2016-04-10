#ifndef SKELETON_SUBSCRIBER_STUB_H
#define SKELETON_SUBSCRIBER_STUB_H

#include <application/iinterrupt.h>

#include <condition_variable>

namespace Stub {

class Subscriber : public Module::ISubscriber {
public:
  Subscriber()
    : _condition()
    , _mutex()
    , _notified(false)
  {
  }

  virtual void notify() override final
  {
    std::lock_guard<std::mutex> lock(_mutex);
    _notified = true;
    _condition.notify_all();
  }

  bool notified_in(std::chrono::milliseconds const & milliseconds)
  {
    std::unique_lock<std::mutex> lock(_mutex);
    bool const notified = _condition.wait_for(lock, milliseconds, [&] { return _notified; });
    _notified = false;
    return notified;
  }

private:
  std::condition_variable _condition;
  std::mutex _mutex;
  bool _notified;
};

}

#endif //SKELETON_SUBSCRIBER_STUB_H
