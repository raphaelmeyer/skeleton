#include <stdbool.h>

#include <device/device.h>

int main()
{
  Device_init();
  while(true) {
    Device_loop();
  }
}

