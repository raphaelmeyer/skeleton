#include <gmock/gmock.h>

#include <app/spi.h>
#include <app/device.h>

using namespace ::testing;

namespace {

  class DeviceMock : public WS::IDevice {
    public:
      MOCK_METHOD0(read, std::vector<unsigned char>());
      MOCK_METHOD1(write, void(std::vector<unsigned char> const & data));
      MOCK_METHOD2(ioctl, void(std::int32_t control, void * value));
  };


  TEST(A_spi_device, uses_ioctl_to_set_the_speed) {
    DeviceMock device;
    WS::Spi testee(device);

    testee.set(WS::Spi::Speed::_500_kHz);
  }

}

