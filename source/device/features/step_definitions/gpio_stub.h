#ifndef SKELETON_GPIO_STUB_H
#define SKELETON_GPIO_STUB_H

#include <device/gpio.h>

#include <thread>
#include <chrono>

struct GpioStruct
{
  IGpio interface;
  Signal signal;
};

class GpioStub
{
public:
  GpioStub()
  {
    _impl.interface.get_signal = GpioStub::get_signal;
    _impl.signal = Signal_Undefined;
  }

  void press()
  {
    using namespace std::chrono_literals;
    _impl.signal = Signal_High;
    std::this_thread::sleep_for(1s);
    _impl.signal = Signal_Low;
  }

  static Signal get_signal(IGpio * base)
  {
    GpioStruct * self = (GpioStruct *)base;
    return self->signal;
  }

  GpioStruct & impl() { return _impl; }

private:
  GpioStruct _impl;

};

#endif //SKELETON_GPIO_STUB_H
