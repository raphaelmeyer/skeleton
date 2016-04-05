#include <application/application.h>
#include <application/shell.h>
#include <application/doorbell.h>

int main() {
  Module::Doorbell doorbell;
  Module::Shell shell;

  Module::Application app(doorbell, shell);

  doorbell.start();

  app.init();
  app.run();

  doorbell.stop();
}

