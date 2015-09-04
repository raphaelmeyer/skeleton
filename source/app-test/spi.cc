#include <gmock/gmock.h>

#include <app/spi.h>

using namespace ::testing;

TEST(A_spi_device, uses_ioctl_to_set_the_speed) {

  WS::Spi testee;

  testee.set(WS::Spi::Speed::_500_kHz);
}

