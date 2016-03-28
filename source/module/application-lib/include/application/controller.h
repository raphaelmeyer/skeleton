#ifndef SKELETON_CONTROLLER_H
#define SKELETON_CONTROLLER_H

#include "application/iinterrupt.h"

namespace Module
{

class ICommand;

class Controller : public ISubscriber
{
public:
  Controller(ICommand & shell);

  virtual void notify() override final;

private:
  ICommand & _shell;
};

}

#endif //SKELETON_CONTROLLER_H
