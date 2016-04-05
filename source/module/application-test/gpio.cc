#include <gmock/gmock.h>

#include <application/gpio.h>

using namespace testing;

namespace {

TEST(A_gpio_path, has_a_number) {
  uint32_t const gpio_number = 19;
  Module::Gpio::Path gpio(gpio_number);

  ASSERT_THAT(gpio.number(), Eq(gpio_number));
}

TEST(A_gpio_path, has_a_general_enable_location) {
  ASSERT_THAT(Module::Gpio::Path::enable(), StrEq("/sys/class/gpio/export"));
}

TEST(A_gpio_path, has_a_direction_file) {
  uint32_t const gpio_number = 20;
  Module::Gpio::Path gpio(gpio_number);

  ASSERT_THAT(gpio.direction(), StrEq("/sys/class/gpio/gpio20/direction"));
}

TEST(A_gpio_path, DISABLED_has_an_edge_file) {
  uint32_t const gpio_number = 21;
  Module::Gpio::Path gpio(gpio_number);

  ASSERT_THAT(gpio.edge(), StrEq("/sys/class/gpio/gpio21/edge"));
}

TEST(A_gpio_path, DISABLED_has_a_value_file) {
  uint32_t const gpio_number = 22;
  Module::Gpio::Path gpio(gpio_number);

  ASSERT_THAT(gpio.value(), StrEq("/sys/class/gpio/gpio22/value"));
}

}
