#ifndef SKELETON_ISCHEDULER_H
#define SKELETON_ISCHEDULER_H

#include <future>
#include <functional>

namespace Module {

class IScheduler
{
public:
  virtual std::future<void> schedule(std::function<void()> request) = 0;
};


}

#endif //SKELETON_ISCHEDULER_H
