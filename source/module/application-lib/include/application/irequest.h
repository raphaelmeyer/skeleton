#ifndef PROJECT_IREQUEST_H
#define PROJECT_IREQUEST_H

namespace Module
{

class IRequest
{
public:
  virtual void dispatch() = 0;
};

}

#endif //PROJECT_IREQUEST_H
