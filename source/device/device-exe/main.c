#include <device/device.h>
#include <device/system_tick.h>
#include <device/gpio.h>
#include <device/pwm.h>
#include <device/timer.h>

struct Device device;
struct Pwm bell;
struct Gpio button;
struct Gpio notify;

int main()
{
  SystemTick_init();

  Pwm_init(&bell);

  Gpio_init(&button, Port_D, Pin_7);
  Gpio_init(&notify, Port_B, Pin_0);

  Device_init(&device, (struct IPwm *)&bell, &button, NULL, &notify);
  while(true) {
    Device_loop(&device);
  }

}

