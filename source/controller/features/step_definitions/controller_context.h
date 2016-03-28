#ifndef SKELETON_CONTROLLER_CONTEXT_H_H
#define SKELETON_CONTROLLER_CONTEXT_H_H

#include <application/application.h>
#include <application/icommand.h>

class ISubscriber
{
public:
  virtual void notify() = 0;
};

namespace Stub
{
class Interrupt
{
public:
  virtual void subscribe(ISubscriber const & subscriber)
  {

  }

  void pulse()
  {

  }
};

class Command : public Controller::ICommand
{
public:
  Command()
    : _commands()
  {
  }

  virtual void execute(std::string const & command) override
  {
    _commands.push_back(command);
  }

  auto const & commands() { return _commands; }

private:
  std::vector<std::string> _commands;
};

}

class ControllerContext
{
public:
  ControllerContext()
    : _bell_interrupt()
    , _shell_commands()
    , _application()
  {
  }

  void run_application() { _application.run(); }
  void shutdown_application() { _application.shutdown(); }

  Stub::Interrupt & bell_interrupt() { return _bell_interrupt; }
  auto const & commands() { return _shell_commands.commands(); }

private:
  Stub::Interrupt _bell_interrupt;
  Stub::Command _shell_commands;

  Controller::Application _application;
};

#endif //SKELETON_CONTROLLER_CONTEXT_H_H
