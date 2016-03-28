#ifndef SKELETON_APPLICATION_H
#define SKELETON_APPLICATION_H

#include <mutex>
#include <condition_variable>

namespace Controller {

class Application {
public:
  Application();

  void run();
  void shutdown();

private:
  std::mutex _mutex;
  std::condition_variable _condition;
  bool _shutdown;
};

}

#endif //SKELETON_APPLICATION_H
