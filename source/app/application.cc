#include "inc/app/application.h"

#include <iostream>

namespace WS {

  Application::Application() {
  }

  void Application::run() {
    std::cout << "Start ...\n" << "Run ...\nShutdown ...\nDone.\n";
  }

}

