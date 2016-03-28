#ifndef SKELETON_DOORBELL_H
#define SKELETON_DOORBELL_H

#include "application/iinterrupt.h"

namespace Module {

class Doorbell : public IInterrupt
{
public:
  virtual void subscribe(ISubscriber & subscriber);
};

}

#endif //SKELETON_DOORBELL_H
