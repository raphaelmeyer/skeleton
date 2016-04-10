#include <application/application.h>
#include <application/doorbell.h>
#include <application/poll.h>
#include <application/shell.h>

int main() {
  Module::Poll poll;
  Module::Doorbell doorbell(poll);
  Module::Shell shell;

  Module::Application app(doorbell, shell);

  doorbell.start();

  app.init();
  app.run();

  doorbell.stop();
}

