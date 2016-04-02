#ifndef SKELETON_CONTROLLER_CONTEXT_H_H
#define SKELETON_CONTROLLER_CONTEXT_H_H

#include <application/application.h>
#include <application/icommand.h>
#include <application/iinterrupt.h>

#include <thread>

namespace Stub
{
class Interrupt : public Module::IInterrupt
{
public:
  virtual void subscribe(Module::ISubscriber & subscriber) {
    _subscribers.push_back(subscriber);
  }

  void pulse() {
    for(Module::ISubscriber & subscriber : _subscribers) {
      subscriber.notify();
    }
  }

private:
  std::vector<std::reference_wrapper<Module::ISubscriber>> _subscribers;
};

class Command : public Module::ICommand
{
public:
  Command()
    : _commands()
  {
  }

  virtual void execute(std::string const & command) override {
    _commands.push_back(command);
  }

  auto const & commands() { return _commands; }

private:
  std::vector<std::string> _commands;
};

}

class ModuleContext
{
public:
  ModuleContext()
    : _application_thread()
    , _doorbell()
    , _shell()
    , _application(_doorbell, _shell)
  {
  }

  void run_application() {
    _application_thread = std::thread([&]{
      _application.run();
    });
  }

  void shutdown_application() {
    _application.shutdown();
    _application_thread.join();
  }

  Stub::Interrupt & doorbell() { return _doorbell; }
  auto const & commands() { return _shell.commands(); }

private:
  std::thread _application_thread;

  Stub::Interrupt _doorbell;
  Stub::Command _shell;

  Module::Application _application;
};

#endif //SKELETON_CONTROLLER_CONTEXT_H_H
