//
// Created by valeriisudakov on 25.08.20.
//

#include "InputIDState.h"

InputIDState::InputIDState(std::shared_ptr<State> nextState) : nextState_(std::move(nextState)) {
  stateName_ = "input ID";
  fail = false;
}

InputIDState::~InputIDState() = default;

void InputIDState::Do(Context& context){
  std::cout<<"Input ID: ";
  std::string input;
  std::cin.clear();
  std::getline(std::cin, input);
  if (input.empty()){
    std::cout<<"ID must be non-empty.\n";
    fail = true;
    return;
  }
  if (input.find_first_not_of("0123456789") != std::string::npos){
    std::cout<<"ID must contains only numbers!\n";
    fail = true;
    return;
  }
  auto id = std::atoi(input.c_str());
  if (id > context.tasks.size()){
    std::cout<<"ID out of tasks range.\n";
    fail = true;
    return;
  }
  context.buffer_.id = id;
}

std::shared_ptr<State> InputIDState::ReadAction() {
  return fail ? std::make_shared<InputIDState>(std::move(nextState_)) : std::move(nextState_);
}
