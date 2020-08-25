//
// Created by valeriisudakov on 21.08.20.
//

#include "InputLabelState.h"

InputLabelState::InputLabelState(std::shared_ptr<State> nextState) : nextState_(std::move(nextState)) {
  stateName_ = "input label";
  fail = false;
}

InputLabelState::~InputLabelState() = default;

void InputLabelState::Do(Context& context){
  std::cout<<"Input label: ";
  std::string label;
  std::getline(std::cin, label);
  if (label.empty()){
    std::cout<<"label must be non-empty.\n";
    fail = true;
    return;
  }
  context.buffer_.label = label;
}

std::shared_ptr<State> InputLabelState::ReadAction() {
  return fail ? std::make_shared<InputLabelState>(std::move(nextState_)) : std::move(nextState_);
}
