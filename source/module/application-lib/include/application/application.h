#ifndef SKELETON_APPLICATION_H
#define SKELETON_APPLICATION_H

#include <mutex>
#include <condition_variable>

namespace Module {

class ICommand;
class IInterrupt;

class Application {
public:
  Application(IInterrupt & doorbell, ICommand & shell);

  void run();
  void shutdown();

private:
  void wait_for_shutdown();
  void trigger_shutdown();

  std::mutex _mutex;
  std::condition_variable _condition;
  bool _shutdown;

  IInterrupt & _doorbell;
  ICommand & _shell;
};

}

#endif //SKELETON_APPLICATION_H
