#ifndef SKELETON_APPLICATION_H
#define SKELETON_APPLICATION_H

#include <mutex>
#include <condition_variable>

namespace Controller {

class IInterrupt;
class ICommand;

class Application {
public:
  Application(IInterrupt & doorbell, ICommand & shell);

  void run();
  void shutdown();

private:
  std::mutex _mutex;
  std::condition_variable _condition;
  bool _shutdown;

  IInterrupt & _doorbell;
  ICommand & _shell;
};

}

#endif //SKELETON_APPLICATION_H
