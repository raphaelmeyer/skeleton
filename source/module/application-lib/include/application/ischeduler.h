#ifndef SKELETON_ISCHEDULER_H
#define SKELETON_ISCHEDULER_H

#include <future>
#include <functional>

namespace Module {

class IRequest;

class IScheduler
{
public:
  virtual void schedule(IRequest & request) = 0;
};

}

#endif //SKELETON_ISCHEDULER_H
