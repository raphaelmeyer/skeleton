#include "application/doorbell.h"

#include "application/ipoll.h"

namespace Module {

Doorbell::Doorbell(IPoll & button)
  : _button(button)
  , _gpio(17)
  , _subscribers()
  , _listener()
  , _running(false)
{
}

Doorbell::~Doorbell() {
  _listener.join();
}

void Doorbell::subscribe(ISubscriber & subscriber) {
  _subscribers.emplace_back(subscriber);
}

void Doorbell::start() {
  _button.setup(_gpio);
  _listener = std::thread([&]{
    _running = true;
    while(_running) {
      if(_button.poll()) {
        for(ISubscriber & subscriber : _subscribers) {
          subscriber.notify();
        }
      }
    }
  });
}

void Doorbell::stop() {
  _running = false;
}

}
