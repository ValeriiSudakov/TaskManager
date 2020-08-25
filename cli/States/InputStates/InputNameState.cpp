//
// Created by valeriisudakov on 21.08.20.
//

#include "InputNameState.h"

InputNameState::InputNameState(std::shared_ptr<State> nextState) : nextState_(std::move(nextState)) {
  stateName_ = "input name";
  fail = false;
}

InputNameState::~InputNameState() = default;

void InputNameState::Do(Context& context){
  std::cout<<"Input name: ";
  std::string name;
  std::getline(std::cin, name);
  if (name.empty()){
    std::cout<<"name must be non-empty.\n";
    fail = true;
    return;
  }
  context.buffer_.name = name;
}

std::shared_ptr<State> InputNameState::ReadAction() {
  return fail ? std::move(std::make_shared<InputNameState>(std::move(nextState_))) : std::move(nextState_);
}
