#ifndef SKELETON_APPLICATION_H
#define SKELETON_APPLICATION_H

#include "application/controller.h"
#include "application/scheduler.h"

#include <mutex>
#include <condition_variable>

namespace Module {

class ICommand;
class IInterrupt;

class Application {
public:
  Application(IInterrupt & doorbell, ICommand & shell);

  void init();
  void run();
  void shutdown();

private:
  void wait_for_shutdown();
  void trigger_shutdown();

  IInterrupt & _doorbell;
  ICommand & _shell;

  std::mutex _mutex;
  std::condition_variable _condition;
  bool _shutdown;

  Scheduler _scheduler;
  Controller _controller;
};

}

#endif //SKELETON_APPLICATION_H
