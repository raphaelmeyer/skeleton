#include <device/device.h>
#include <device/gpio.h>
#include <device/pwm.h>

#include <stdbool.h>

struct Device device;
struct Pwm bell;
struct Gpio button;

int main()
{
  Device_init(&device, (struct IPwm *)&bell, &button);
  Device_start(&device);

  while(true);
}

