#ifndef SKELETON_INTERRUPT_STUB_H
#define SKELETON_INTERRUPT_STUB_H

#include <gmock/gmock.h>

#include <application/iinterrupt.h>

namespace Stub {

class Interrupt : public Module::IInterrupt
{
public:
  Interrupt()
    : _subscriber(nullptr)
  {
  }

  virtual void subscribe(Module::ISubscriber & subscriber) {
    _subscriber = &subscriber;
  }

  void pulse() {
    if(_subscriber) {
      _subscriber->notify();
    }
  }

private:
  Module::ISubscriber * _subscriber;
};

} // namespace Stub

#endif //SKELETON_INTERRUPT_STUB_H
