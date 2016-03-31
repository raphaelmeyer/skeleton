#ifndef SKELETON_SCHEDULER_H
#define SKELETON_SCHEDULER_H

#include "ischeduler.h"

namespace Module {

class Scheduler : public IScheduler {
public:
  void start();
  virtual std::future<uint32_t> schedule(std::function<uint32_t()> request) override final;
  virtual std::future<std::string> schedule(std::function<std::string()> request) override final;

private:
  template<typename T>
  std::future<T> dispatch(std::function<T()> request) {
    std::promise<T> promise;
    promise.set_value(request());
    return promise.get_future();
  }
};

}

#endif //SKELETON_SCHEDULER_H
