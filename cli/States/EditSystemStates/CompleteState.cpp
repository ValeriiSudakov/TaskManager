//
// Created by valeriisudakov on 20.08.20.
//

#include "CompleteState.h"
#include "States/BaseState.h"

CompleteState::CompleteState() {
  stateName_ = "complete";
}

CompleteState::~CompleteState() = default;

void CompleteState::Do(Context& context) {
  //doing smth
}

std::shared_ptr<State> CompleteState::ReadAction() {
  //do smth
  return std::make_shared<BaseState>();
}