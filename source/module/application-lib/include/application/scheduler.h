#ifndef SKELETON_SCHEDULER_H
#define SKELETON_SCHEDULER_H

#include "ischeduler.h"

namespace Module {

class Scheduler : public IScheduler {
public:
  virtual std::future<void> schedule(std::function<void()> request) override final {
    return std::future<void>();
  }
};

}

#endif //SKELETON_SCHEDULER_H
