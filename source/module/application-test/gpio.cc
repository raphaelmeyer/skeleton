#include <gmock/gmock.h>

#include <application/gpio.h>

using namespace testing;

namespace {

TEST(A_gpio_path, knows_its_number) {
  uint32_t const gpio_number = 19;
  Module::Gpio::Path gpio(gpio_number);

  ASSERT_THAT(gpio.number(), Eq(gpio_number));
}

}
