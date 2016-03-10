#include <device/device.h>
#include <device/gpio.h>
#include <device/pwm.h>
#include <device/timer.h>

struct Device device;
struct Pwm bell;
struct Gpio button;
struct Timer timer;

int main()
{
  Device_init(&device, (struct IPwm *)&bell, &button, (struct ITimer *)&timer);
  while(true) {
    Device_loop(&device);
  }

}

