//
// Created by valeriisudakov on 25.08.20.
//

#include "InputIDState.h"

InputIDState::InputIDState() {
  stateID_ = StatesID::InputID;
}

InputIDState::~InputIDState() = default;

StateOperationResult InputIDState::Do(const std::shared_ptr<Context>& context){
  std::cout<<"Input ID: ";
  std::string input;
  std::cin.clear();
  std::getline(std::cin, input);
  if (input.empty()){
    std::cout<<"ID must be non-empty.\n";
    return StateOperationResult::INCORRECT_INPUT;
  }
  if (input.find_first_not_of("0123456789") != std::string::npos){
    std::cout<<"ID must contains only numbers!\n";
    return StateOperationResult::INCORRECT_INPUT;
  }
  auto id = std::atoi(input.c_str());
  if (id > context->tasks_.size()-1){
    std::cout<<"ID out of tasks range.\n";
    return StateOperationResult::INCORRECT_INPUT;
  }
  context->buffer_.id = context->tasks_[id].GetTaskId().Get();
  return StateOperationResult::SUCCESS;
}
