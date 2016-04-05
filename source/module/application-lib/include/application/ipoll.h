#ifndef PROJECT_IPOLL_H
#define PROJECT_IPOLL_H

namespace Module {

namespace Gpio { class Path; }

class IPoll {
public:
  virtual void setup(Gpio::Path & gpio) = 0;
  virtual bool poll() = 0;
};

}

#endif //PROJECT_IPOLL_H
