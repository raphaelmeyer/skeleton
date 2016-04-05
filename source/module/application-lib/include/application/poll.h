#ifndef PROJECT_INTERRUPT_H
#define PROJECT_INTERRUPT_H

#include "application/gpio.h"


namespace Module {

class IPoll {
public:
  virtual void setup(Gpio::Path & gpio) = 0;
  virtual bool poll() = 0;
};

class Poll : public IPoll
{
public:
  Poll();

  virtual void setup(Gpio::Path & gpio);
  virtual bool poll();

private:
  int _poll_fd;
};

}

#endif //PROJECT_INTERRUPT_H
