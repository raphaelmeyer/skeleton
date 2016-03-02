#ifndef SKELETON_GPIO_STUB_H
#define SKELETON_GPIO_STUB_H

#include <device/gpio.h>

#include <thread>
#include <chrono>
#include <avr/io.h>

class ButtonStub
{
public:
  ButtonStub(uint8_t volatile * pin_register, uint8_t pin)
  {
    _pin_register = pin_register;
    _pin = pin;
  }

  void press()
  {
    // TODO bounce/chatter
    using namespace std::chrono_literals;
    *_pin_register |= (1 << _pin);
    std::this_thread::sleep_for(1s);
    *_pin_register &= ~(1 << _pin);
  }

private:
  uint8_t volatile * _pin_register;
  uint8_t _pin;
};

#endif //SKELETON_GPIO_STUB_H
