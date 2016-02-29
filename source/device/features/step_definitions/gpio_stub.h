#ifndef SKELETON_GPIO_STUB_H
#define SKELETON_GPIO_STUB_H

#include <device/gpio.h>

#include <thread>
#include <chrono>
#include <avr/io.h>

class ButtonStub
{
public:
  ButtonStub()
  {
    _port = &PINB;
    _pin = 0;
  }

  void press()
  {
    // TODO bounce/chatter
    using namespace std::chrono_literals;
    *_port |= (1 << _pin);
    std::this_thread::sleep_for(1s);
    *_port &= ~(1 << _pin);
  }

private:
  uint8_t volatile * _port;
  uint8_t _pin;
};

#endif //SKELETON_GPIO_STUB_H
