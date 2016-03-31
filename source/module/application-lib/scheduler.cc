#include "application/scheduler.h"

#include "application/irequest.h"
#include "application/request.h"

namespace Module {

void Scheduler::start() {
}

void Scheduler::schedule(IRequest & request) {
  request.dispatch();
}

std::future<uint32_t> Scheduler::schedule(std::function<uint32_t()> request) {
  Request<uint32_t> r{request};
  schedule(r);
  return r.get_future();
}

std::future<std::string> Scheduler::schedule(std::function<std::string()> request) {
  Request<std::string> r{request};
  schedule(r);
  return r.get_future();
}

}
