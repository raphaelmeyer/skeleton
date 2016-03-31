#ifndef SKELETON_SCHEDULER_MOCK_H
#define SKELETON_SCHEDULER_MOCK_H

#include <gmock/gmock.h>

#include <application/ischeduler.h>
#include <application/irequest.h>

namespace Mock {

class Scheduler : public Module::IScheduler
{
public:
  MOCK_METHOD1(schedule, void(Module::IRequest & request));
};

}

#endif //SKELETON_SCHEDULER_MOCK_H
