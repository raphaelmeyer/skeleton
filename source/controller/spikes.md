# I2C

## wiring

    rpi           ada 757        arduino
    -------       --------       -------
    1 (3.3)  ---  LV    HV  ---  5V
    3 (SDA)  ---  A1    B1  ---  A4
    5 (SCL)  ---  A2    B2  ---  A5
    9 (GND)  ---  GND  GND  ---  GND

## arduino sketch

    #include "Wire.h"
    
    uint8_t value = 0;
    uint8_t reg = 0;
    
    void setup() {
      Wire.begin(0x31);
      Wire.onReceive(_receive);
      Wire.onRequest(_send);
    }
    
    void loop() {
      delay(100);
    }
    
    void _send() {
      uint8_t res[2] = { reg, value };
      Wire.write(res, 2);
    }
    
    void _receive(int num) {
      while(Wire.available() > 0) {
        reg = Wire.read();
        value++;
      }
    }

## rpi

[i2c-dev](https://www.kernel.org/doc/Documentation/i2c/dev-interface)
