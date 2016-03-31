#include "application/scheduler.h"

namespace Module {

void Scheduler::start() {
}

class IRequest {
public:
  virtual void dispatch() = 0;
};

template<typename T>
class Request : public IRequest
{
public:
  Request(std::function<T()> request)
    : _request(request)
  {}

  virtual void dispatch() override final {
    _promise.set_value(_request());
  }

  std::function<T()> _request;
  std::promise<T> _promise;
};

std::future<uint32_t> Scheduler::schedule(std::function<uint32_t()> request) {
  Request<uint32_t> r{request};
  r.dispatch();
  return r._promise.get_future();
}

std::future<std::string> Scheduler::schedule(std::function<std::string()> request) {
  Request<std::string> r{request};
  r.dispatch();
  return r._promise.get_future();
}


}
