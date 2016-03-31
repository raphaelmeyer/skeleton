#include "application/scheduler.h"

namespace Module {

void Scheduler::start() {
}

std::future<uint32_t> Scheduler::schedule(std::function<uint32_t()> request) {
  std::promise<uint32_t> promise;
  promise.set_value(request());
  return promise.get_future();
}


}
