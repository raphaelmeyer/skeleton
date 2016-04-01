#include "application/scheduler.h"

#include "application/irequest.h"
#include "application/request.h"

namespace Module {

void Scheduler::start() {
}

void Scheduler::schedule(IRequest & request) {
  std::lock_guard<std::mutex> lock(_mutex);
  request.dispatch();
}

}
