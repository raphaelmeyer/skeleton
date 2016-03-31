#ifndef SKELETON_ISCHEDULER_H
#define SKELETON_ISCHEDULER_H

#include <future>
#include <functional>

namespace Module {

class IScheduler
{
public:
  virtual std::future<uint32_t> schedule(std::function<uint32_t()> request) = 0;
};


}

#endif //SKELETON_ISCHEDULER_H
