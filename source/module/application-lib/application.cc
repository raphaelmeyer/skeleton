#include "application/application.h"

#include "application/icommand.h"
#include "application/controller.h"
#include "application/scheduler.h"

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
  Scheduler scheduler;
  Controller controller(_shell, scheduler);
  _doorbell.subscribe(controller);

  wait_for_shutdown();
}

void Application::shutdown() {
  trigger_shutdown();
}

void Application::wait_for_shutdown()
{
  std::unique_lock<std::mutex> lock(_mutex);
  _condition.wait(lock, [this]{ return _shutdown; });
}

void Application::trigger_shutdown()
{
  {
    std::lock_guard<std::mutex> lock(_mutex);
    _shutdown = true;
  }
  _condition.notify_all();
}

}
