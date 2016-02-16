# I2C + interrupt

## wiring

    rpi           ada 757        arduino
    -------       --------       -------
    1 (3.3)  ---  LV    HV  ---  5V
    3 (SDA)  ---  A1    B1  ---  A4
    5 (SCL)  ---  A2    B2  ---  A5
                  A3    B3
    11 (17)  ---  A4    B4  ---  13
    9 (GND)  ---  GND  GND  ---  GND

## Arduino

    #include "Wire.h"
    
    uint8_t value = 0;
    uint8_t reg = 0;
    
    void setup() {
      // i2c
      Wire.begin(0x31);
      Wire.onReceive(_receive);
      Wire.onRequest(_send);
    
      // gpio
      pinMode(13, OUTPUT);
      digitalWrite(13, LOW);
    }
    
    void loop() {
      delay(1500);
      digitalWrite(13, HIGH);
      delay(10);
      digitalWrite(13, LOW);
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

## Raspberry PI

### I2C

[i2c-dev](https://www.kernel.org/doc/Documentation/i2c/dev-interface)

### GPIO/interrupt

[sysfs](https://www.kernel.org/doc/Documentation/gpio/sysfs.txt)


