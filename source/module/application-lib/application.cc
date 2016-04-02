#include "application/application.h"

#include "application/icommand.h"

namespace Module {

Application::Application(IInterrupt & doorbell, ICommand & shell)
  : _doorbell(doorbell)
  , _shell(shell)
  , _mutex()
  , _condition()
  , _shutdown(false)
  , _scheduler()
  , _controller(_shell, _scheduler)
{
}

void Application::init() {
  _doorbell.subscribe(_controller);
}

void Application::run() {
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
