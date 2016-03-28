#include "application/application.h"

#include "application/icommand.h"
#include "application/controller.h"

namespace Module {

Application::Application(IInterrupt & doorbell, ICommand & shell)
  : _mutex()
  , _condition()
  , _shutdown(false)
  , _doorbell(doorbell)
  , _shell(shell)
{
}

void Application::run() {
  Controller controller(_shell);
  _doorbell.subscribe(controller);

  std::unique_lock<std::mutex> lock(_mutex);
  _condition.wait(lock, [this]{ return _shutdown; });
}

void Application::shutdown() {
  {
    std::lock_guard<std::mutex> lock(_mutex);
    _shutdown = true;
  }
  _condition.notify_all();
}

}
