#include "application/controller.h"

#include "application/icommand.h"
#include "application/ischeduler.h"
#include "application/request.h"

namespace Module {

Controller::Controller(ICommand & shell, IScheduler & scheduler)
  : _shell(shell)
  , _scheduler(scheduler)
{
}

void Controller::notify()
{
  Request<void> request{[this]{
    _shell.execute("raspistill");
  }};
  _scheduler.schedule(request);
}

}
