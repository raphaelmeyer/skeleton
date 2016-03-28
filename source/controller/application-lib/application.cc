#include "application/application.h"

namespace Controller {

Application::Application()
  : _mutex()
  , _condition()
  , _shutdown(false)
{
}

void Application::run() {
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
