#ifndef APP_DEVICE_H
#define APP_DEVICE_H

#include <vector>
#include <cstdint>

namespace WS {

  class IDevice {
    public:
      virtual std::vector<unsigned char> read() = 0;
      virtual void write(std::vector<unsigned char> const & data) = 0;
      virtual void ioctl(std::int32_t control, void * value) = 0;
  };

  class Device : public IDevice {
  };

};

#endif

