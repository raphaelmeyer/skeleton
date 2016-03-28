#ifndef SKELETON_IINTERRUPT_H
#define SKELETON_IINTERRUPT_H

namespace Module {

class ISubscriber
{
public:
  virtual void notify() = 0;
};

class IInterrupt
{
public:
  virtual void subscribe(ISubscriber & subscriber) = 0;
};

}

#endif //SKELETON_IINTERRUPT_H
