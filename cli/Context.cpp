//
// Created by valeriisudakov on 18.08.20.
//

#include "Context.h"

Context::Context(std::shared_ptr<State> state) {
  this->TransitionTo(state);
}

Context::~Context() = default;

void Context::TransitionTo(std::shared_ptr<State> state){
  state_ = state;
}

void Context::Request() {
  state_->ReadAction();
}