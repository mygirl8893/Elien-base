#include "ContextGroup.h"
#include <cassert>

namespace System {

ContextGroup::ContextGroup(Dispatcher& dispatcher) : dispatcher(&dispatcher) {
  contextGroup.firstContext = nullptr;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
ContextGroup::ContextGroup(ContextGroup&& other) : dispatcher(other.dispatcher) {
  if (dispatcher != nullptr) {
    assert(other.contextGroup.firstContext == nullptr);
    contextGroup.firstContext = nullptr;
    other.dispatcher = nullptr;
  }
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
ContextGroup::~ContextGroup() {
  if (dispatcher != nullptr) {
    interrupt();
    wait();
  }
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
ContextGroup& ContextGroup::operator=(ContextGroup&& other) {
  assert(dispatcher == nullptr || contextGroup.firstContext == nullptr);
  dispatcher = other.dispatcher;
  if (dispatcher != nullptr) {
    assert(other.contextGroup.firstContext == nullptr);
    contextGroup.firstContext = nullptr;
    other.dispatcher = nullptr;
  }

  return *this;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
void ContextGroup::interrupt() {
  assert(dispatcher != nullptr);
  for (NativeContext* context = contextGroup.firstContext; context != nullptr; context = context->groupNext) {
    dispatcher->interrupt(context);
  }
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
void ContextGroup::spawn(std::function<void()>&& procedure) {
  assert(dispatcher != nullptr);
  NativeContext& context = dispatcher->getReusableContext();
  if (contextGroup.firstContext != nullptr) {
    context.groupPrev = contextGroup.lastContext;
    assert(contextGroup.lastContext->groupNext == nullptr);
    contextGroup.lastContext->groupNext = &context;
  } else {
    context.groupPrev = nullptr;
    contextGroup.firstContext = &context;
    contextGroup.firstWaiter = nullptr;
  }

  context.interrupted = false;
  context.group = &contextGroup;
  context.groupNext = nullptr;
  context.procedure = std::move(procedure);
  contextGroup.lastContext = &context;
  dispatcher->pushContext(&context);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
void ContextGroup::wait() {
  if (contextGroup.firstContext != nullptr) {
    NativeContext* context = dispatcher->getCurrentContext();
    context->next = nullptr;
    if (contextGroup.firstWaiter != nullptr) {
      assert(contextGroup.lastWaiter->next == nullptr);
      contextGroup.lastWaiter->next = context;
    } else {
      contextGroup.firstWaiter = context;
    }

    contextGroup.lastWaiter = context;
    dispatcher->dispatch();
    assert(context == dispatcher->getCurrentContext());
  }
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
}
