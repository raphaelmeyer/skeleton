#ifndef SKELETON_PWM_SPY_H
#define SKELETON_PWM_SPY_H

#include <vector>

class PwmSpy
{
public:
  PwmSpy()
    : _events()
  {
  }

  struct Event{};

  std::vector<Event> const & events() { return _events; }

private:
  std::vector<Event> _events;
};

#endif //SKELETON_PWM_SPY_H
