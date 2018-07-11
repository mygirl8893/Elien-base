#include "Event.h"
#include <cassert>
#include <System/Dispatcher.h>
#include <System/InterruptedException.h>

namespace System {

namespace {

struct EventWaiter {
  bool interrupted;
  EventWaiter* prev;
  EventWaiter* next;
  NativeContext* context;
};

}

Event::Event() : dispatcher(nullptr) {
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
Event::Event(Dispatcher& dispatcher) : dispatcher(&dispatcher), state(false), first(nullptr) {
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
Event::Event(Event&& other) : dispatcher(other.dispatcher) {
  if (dispatcher != nullptr) {
    state = other.state;
    if (!state) {
      assert(other.first == nullptr);
      first = nullptr;
    }

    other.dispatcher = nullptr;
  }
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
Event::~Event() {
  assert(dispatcher == nullptr || state || first == nullptr);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
Event& Event::operator=(Event&& other) {
  assert(dispatcher == nullptr || state || first == nullptr);
  dispatcher = other.dispatcher;
  if (dispatcher != nullptr) {
    state = other.state;
    if (!state) {
      assert(other.first == nullptr);
      first = nullptr;
    }

    other.dispatcher = nullptr;
  }

  return *this;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool Event::get() const {
  assert(dispatcher != nullptr);
  return state;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
void Event::clear() {
  assert(dispatcher != nullptr);
  if (state) {
    state = false;
    first = nullptr;
  }
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
void Event::set() {
  assert(dispatcher != nullptr);
  if (!state) {
    state = true;
    for (EventWaiter* waiter = static_cast<EventWaiter*>(first); waiter != nullptr; waiter = waiter->next) {
      waiter->context->interruptProcedure = nullptr;
      dispatcher->pushContext(waiter->context);
    }
  }
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
void Event::wait() {
  assert(dispatcher != nullptr);
  if (dispatcher->interrupted()) {
    throw InterruptedException();
  }

  if (!state) {
    EventWaiter waiter = { false, nullptr, nullptr, dispatcher->getCurrentContext() };
    waiter.context->interruptProcedure = [&] {
      if (waiter.next != nullptr) {
        assert(waiter.next->prev == &waiter);
        waiter.next->prev = waiter.prev;
      } else {
        assert(last == &waiter);
        last = waiter.prev;
      }

      if (waiter.prev != nullptr) { 
        assert(waiter.prev->next == &waiter);
        waiter.prev->next = waiter.next;
      } else {
        assert(first == &waiter);
        first = waiter.next;
      }

      assert(!waiter.interrupted);
      waiter.interrupted = true;
      dispatcher->pushContext(waiter.context);
    };

    if (first != nullptr) {
      static_cast<EventWaiter*>(last)->next = &waiter;
      waiter.prev = static_cast<EventWaiter*>(last);
    } else {
      first = &waiter;
    }

    last = &waiter;
    dispatcher->dispatch();
    assert(waiter.context == dispatcher->getCurrentContext());
    assert( waiter.context->interruptProcedure == nullptr);
    assert(dispatcher != nullptr);
    if (waiter.interrupted) {
      throw InterruptedException();
    } 
  }
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
}
