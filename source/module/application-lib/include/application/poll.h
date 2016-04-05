#ifndef PROJECT_INTERRUPT_H
#define PROJECT_INTERRUPT_H

#include "application/ipoll.h"

namespace Module {

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
