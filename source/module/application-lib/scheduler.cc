#include "application/scheduler.h"

namespace Module {

void Scheduler::start() {
}

std::future<void> Scheduler::schedule(std::function<void()> request) {
  request();
  return std::future<void>();
}


}
