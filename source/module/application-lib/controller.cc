#include "application/controller.h"

#include "application/icommand.h"
#include "application/ischeduler.h"

namespace Module {

Controller::Controller(ICommand & shell, IScheduler & scheduler)
  : _shell(shell)
  , _scheduler(scheduler)
{
}

void Controller::notify()
{
  _scheduler.schedule([this]{ return 0; });
  _shell.execute("raspistill");
}

}
