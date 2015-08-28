#ifndef APP_APPLICATION_H
#define APP_APPLICATION_H

#include <string>

namespace WS {

  class Application {
    public:
      Application();

      void run();

    private:
      void abort(std::string const & message);

      int _fd;
  };

}

#endif

