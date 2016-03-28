#include "application/controller.h"

#include "application/icommand.h"

namespace Controller {

Controller::Controller(ICommand & shell)
  : _shell(shell)
{
}

void Controller::notify()
{
  _shell.execute("raspistill");
}

}
