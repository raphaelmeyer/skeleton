#ifndef APP_APPLICATION_H
#define APP_APPLICATION_H

#include <string>
#include <cstdint>

namespace WS
{

  class Application
  {
  public:
    Application();

    void run();

  private:
    void abort(std::string const & message);
    void get_register(int const address, std::uint8_t reg);
    void i2c_example();
    void int_example();

    int _fd;
  };

}

#endif

