//
// Created by valeriisudakov on 20.08.20.
//

#include "CompleteState.h"
#include "CorrectInput.h"

CompleteState::CompleteState() {
  stateName_ = "complete";
  nextStates_.insert("base");
  nextStates_.insert("exit");
}

CompleteState::~CompleteState() = default;

void CompleteState::Do(Context& context) {
  std::cout<<"Input number of task to complete: ";
  auto number = CorrectInput::Number();
  if (!number.has_value()){
    std::cout<<"Incorrect input of number.\n";
    return;
  }
}
