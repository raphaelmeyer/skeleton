#ifndef SKELETON_SCHEDULER_MOCK_H
#define SKELETON_SCHEDULER_MOCK_H

#include <gmock/gmock.h>

#include <application/ischeduler.h>
#include <application/irequest.h>

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

  virtual std::future<std::string> schedule(std::function<std::string()> request)
  {
    schedule_proxy(request);
    std::promise<std::string> promise;
    promise.set_value("");
    return promise.get_future();
  }

  MOCK_METHOD1(schedule, void(Module::IRequest & request));

  MOCK_METHOD1(schedule_proxy, void(std::function<uint32_t()> request));
  MOCK_METHOD1(schedule_proxy, void(std::function<std::string()> request));
};

}

#endif //SKELETON_SCHEDULER_MOCK_H
