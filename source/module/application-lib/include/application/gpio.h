#ifndef PROJECT_GPIO_H
#define PROJECT_GPIO_H

#include <string>

namespace Module {
namespace Gpio {

class Path {
public:
  Path(uint32_t number);

  uint32_t number() const;
  std::string const & enable() const;
  std::string const & direction() const;
  std::string const & edge() const;
  std::string const & value() const;

private:
  uint32_t _number;
};

}
}

#endif //PROJECT_GPIO_H
