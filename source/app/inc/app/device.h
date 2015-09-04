#ifndef APP_DEVICE_H
#define APP_DEVICE_H

namespace WS {

  class IDevice {
    public:
      std::vector<unsigned char> read() = 0;
      void write(std::vector<unsigned char> data) = 0;
      void ioctl(int32_t control, void * value) = 0;
  }

  class Device : public IDevice {
  };

};

#endif

