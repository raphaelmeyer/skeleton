#ifndef SKELETON_DOORBELL_H
#define SKELETON_DOORBELL_H

#include "application/iinterrupt.h"

#include "application/poll.h"
#include "application/gpio.h"

#include <vector>
#include <thread>

namespace Module {

class Doorbell : public IInterrupt
{
public:
  Doorbell();

  virtual void subscribe(ISubscriber & subscriber);

  void start();
  void stop();

private:
  Gpio::Path _gpio;
  Poll _poll;
  std::thread _listener;

  std::vector<std::reference_wrapper<ISubscriber>> _subscribers;

  bool _running;
};

}

#endif //SKELETON_DOORBELL_H
