//
// Created by valeriisudakov on 20.08.20.
//

#include "PostponeState.h"
#include "CorrectInput.h"

PostponeState::PostponeState() {
  stateName_ = "postpone";
  nextStates_.insert("base");
  nextStates_.insert("exit");
}

PostponeState::~PostponeState() = default;

void PostponeState::Do(Context& context) {
  std::cout<<"Input number of task to postpone: ";
  auto number = CorrectInput::Number();
  if (!number.has_value()){
    std::cout<<"Incorrect input of number.\n";
    return;
  }
}
