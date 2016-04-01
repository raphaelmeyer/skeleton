#ifndef PROJECT_REQUEST_H
#define PROJECT_REQUEST_H

#include "application/irequest.h"

#include <future>
#include <functional>

namespace Module {

template<typename T>
class Request : public IRequest
{
public:
  Request(std::function<T()> request)
    : _request(request)
  {
  }

  virtual void dispatch() override final
  {
    _promise.set_value(_request());
  }

  std::future <T> get_future()
  {
    return _promise.get_future();
  }

private:
  std::function<T()> _request;
  std::promise <T> _promise;
};

template<>
void Request<void>::dispatch();

}

#endif //PROJECT_REQUEST_H
