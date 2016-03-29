#ifndef SKELETON_SCHEDULER_MOCK_H
#define SKELETON_SCHEDULER_MOCK_H

#include <gmock/gmock.h>

#include <application/ischeduler.h>

namespace Mock {

class Scheduler : public Module::IScheduler
{
public:
  virtual std::future<void> schedule(std::function<void()> request)
  {
    schedule_proxy(request);
    std::promise<void> promise;
    promise.set_value();
    return promise.get_future();
  }

  MOCK_METHOD1(schedule_proxy, void(std::function<void()>
  request));
};

}

#endif //SKELETON_SCHEDULER_MOCK_H
