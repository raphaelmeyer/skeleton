#include "application/scheduler.h"

namespace Module {

void Scheduler::start() {
}

std::future<uint32_t> Scheduler::schedule(std::function<uint32_t()> request) {
  return dispatch(request);
}

std::future<std::string> Scheduler::schedule(std::function<std::string()> request) {
  return dispatch(request);
}


}
