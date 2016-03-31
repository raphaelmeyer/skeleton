#ifndef SKELETON_SCHEDULER_MOCK_H
#define SKELETON_SCHEDULER_MOCK_H

#include <gmock/gmock.h>

#include <application/ischeduler.h>

namespace Mock {

class Scheduler : public Module::IScheduler
{
public:
  virtual std::future<uint32_t> schedule(std::function<uint32_t()> request)
  {
    schedule_proxy(request);
    std::promise<uint32_t> promise;
    promise.set_value(0);
    return promise.get_future();
  }

  MOCK_METHOD1(schedule_proxy, void(std::function<uint32_t()> request));
};

}

#endif //SKELETON_SCHEDULER_MOCK_H
