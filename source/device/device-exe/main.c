#include <device/device.h>
#include <device/system_tick.h>
#include <device/gpio.h>
#include <device/pwm.h>
#include <device/timer.h>

struct Device device;
struct Pwm bell;
struct Gpio button;
struct Timer timer;
struct Gpio notify;

int main()
{
  SystemTick_init();

  Gpio_init(&button, Port_D, Pin_7);
  Pwm_init(&bell);
  Timer_init(&timer);

  Device_init(&device, (struct IPwm *)&bell, &button, &timer, &notify);
  while(true) {
    Device_loop(&device);
  }

}

