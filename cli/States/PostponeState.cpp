//
// Created by valeriisudakov on 20.08.20.
//

#include "PostponeState.h"

PostponeState::PostponeState() {
  stateName_ = "postpone";
  nextStates_.insert("base");
  nextStates_.insert("exit");
}

PostponeState::~PostponeState() = default;

void PostponeState::Do(Context& context) {
  std::cout<<stateName_<<" is doing \n";
}
