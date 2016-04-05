#ifndef PROJECT_GPIO_H
#define PROJECT_GPIO_H

#include <string>

namespace Module {
namespace Gpio {

class Path {
public:
  Path(uint32_t number);

  static std::string const & enable();

  uint32_t number() const;
  std::string const & direction() const;
  std::string const & edge() const;
  std::string const & value() const;

private:
  uint32_t const _number;

  std::string const _direction;

  static std::string const Base;
  static std::string const Enable;
};

}
}

#endif //PROJECT_GPIO_H
