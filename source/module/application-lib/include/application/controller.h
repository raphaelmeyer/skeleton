#ifndef SKELETON_CONTROLLER_H
#define SKELETON_CONTROLLER_H

#include "application/iinterrupt.h"

namespace Module
{

class ICommand;
class IScheduler;

class Controller : public ISubscriber
{
public:
  Controller(ICommand & shell, IScheduler & scheduler);

  virtual void notify() override final;

private:
  void take_picture();

  ICommand & _shell;
  IScheduler & _scheduler;
};

}

#endif //SKELETON_CONTROLLER_H
