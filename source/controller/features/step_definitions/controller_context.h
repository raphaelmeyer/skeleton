#ifndef SKELETON_CONTROLLER_CONTEXT_H_H
#define SKELETON_CONTROLLER_CONTEXT_H_H

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

class Command
{
public:
  Command()
    : _commands()
  {
  }

  std::vector<std::string> const & list() { return _commands; }

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
  {
  }

  Stub::Interrupt & bell_interrupt() { return _bell_interrupt; }
  Stub::Command & commands() { return _shell_commands; }

private:
  Stub::Interrupt _bell_interrupt;
  Stub::Command _shell_commands;

  // Controller::Application _application;
};

#endif //SKELETON_CONTROLLER_CONTEXT_H_H
