#include <application/application.h>
#include <application/shell.h>
#include <application/doorbell.h>

int main() {
  Controller::Doorbell doorbell;
  Controller::Shell shell;

  Controller::Application app(doorbell, shell);

  app.run();
}

