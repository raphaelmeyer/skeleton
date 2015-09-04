#ifndef APP_SPI_H
#define APP_SPI_H


namespace WS {

  class IDevice;

  class Spi {
    public:
      enum class Speed {
        Undefined,
        _500_kHz
      };

      Spi(IDevice & device);

      void set(Speed speed);
  };

}

#endif

