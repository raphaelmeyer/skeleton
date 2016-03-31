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
  Request<uint32_t> request{[]{ return 0; }};
  _scheduler.schedule(request);
  _shell.execute("raspistill");
}

}
