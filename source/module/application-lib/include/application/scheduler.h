#ifndef SKELETON_SCHEDULER_H
#define SKELETON_SCHEDULER_H

#include "ischeduler.h"

namespace Module {

class Scheduler : public IScheduler {
public:
  void start();

  virtual void schedule(IRequest & request) override final;
};

}

#endif //SKELETON_SCHEDULER_H
