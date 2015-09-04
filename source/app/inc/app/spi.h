#ifndef APP_SPI_H
#define APP_SPI_H

namespace WS {

  class Spi {
    public:
      enum class Speed {
        Undefined,
        _500_kHz,
      };


      void set(Speed speed);
  };

}

#endif

