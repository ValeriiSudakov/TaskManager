//
// Created by valeriisudakov on 20.08.20.
//

#include "CompleteState.h"

CompleteState::CompleteState() {
  stateName_ = "complete";
  nextStates_.insert("base");
  nextStates_.insert("exit");
}

CompleteState::~CompleteState() = default;

void CompleteState::Do(Context& context) {
  std::cout<<stateName_<<" is doing \n";
}

void CompleteState::PrintActions() {}