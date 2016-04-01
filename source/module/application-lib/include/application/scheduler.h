#ifndef SKELETON_SCHEDULER_H
#define SKELETON_SCHEDULER_H

#include "ischeduler.h"

#include <mutex>

namespace Module {

class Scheduler : public IScheduler {
public:
  void start();

  virtual void schedule(IRequest & request) override final;

private:
  std::mutex _mutex;
};

}

#endif //SKELETON_SCHEDULER_H
