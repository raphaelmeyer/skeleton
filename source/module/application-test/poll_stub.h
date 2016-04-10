#ifndef SKELETON_POLL_STUB_H
#define SKELETON_POLL_STUB_H

#include <application/ipoll.h>
#include <application/gpio.h>

#include <condition_variable>

namespace Stub
{

class Poll : public Module::IPoll
{
public:
  Poll()
    : _condition()
    , _mutex()
    , _result(false)
    , _ready(false)
    , _setup(false)
    , _gpio(0)
  {
  }

  virtual void setup(Module::Gpio::Path const & gpio) override final
  {
    _gpio = gpio.number();
    _setup = true;
  }

  virtual bool poll() override final
  {
    std::unique_lock <std::mutex> wait_lock(_mutex);
    _condition.wait(wait_lock, [&] { return _ready; });
    _ready = false;
    return _result;
  }

  bool is_set_up() const
  {
    return _setup;
  }

  uint32_t configured_gpio() const
  {
    return _gpio;
  }

  void trigger(bool result)
  {
    std::lock_guard <std::mutex> lock(_mutex);
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

}

#endif //SKELETON_POLL_STUB_H
