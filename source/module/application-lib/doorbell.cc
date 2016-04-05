#include "application/doorbell.h"

namespace Module {

Doorbell::Doorbell()
  : _gpio(17)
  , _poll()
  , _listener()
  , _subscribers()
  , _running(false)
{
}

void Doorbell::subscribe(ISubscriber & subscriber) {
  _subscribers.emplace_back(subscriber);
}

void Doorbell::start() {
  _poll.setup(_gpio);
  _running = true;
  _listener = std::thread([this]{
    while(_running) {
      if (_poll.poll()) {
        for(ISubscriber & subscriber : _subscribers) {
          subscriber.notify();
        }
      }
    }
  });
}

void Doorbell::stop() {
  _running = false;
  _listener.join();
}

}