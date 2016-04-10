#ifndef SKELETON_DOORBELL_H
#define SKELETON_DOORBELL_H

#include "application/iinterrupt.h"
#include "application/gpio.h"

#include <thread>
#include <vector>

namespace Module {

class IPoll;

class Doorbell : public IInterrupt
{
public:
  Doorbell(IPoll & button);
  ~Doorbell();

  virtual void subscribe(ISubscriber & subscriber);

  void start();
  void stop();

private:
  IPoll & _button;

  Gpio::Path const _gpio;

  std::vector<std::reference_wrapper<ISubscriber>> _subscribers;
  std::thread _listener;

  bool _running;
};

}

#endif //SKELETON_DOORBELL_H
