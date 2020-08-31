//
// Created by valeriisudakov on 21.08.20.
//

#include "InputLabelState.h"

InputLabelState::InputLabelState() : State(StatesID::InputLabel){}

InputLabelState::~InputLabelState() = default;

StateOperationResult InputLabelState::Do(const std::shared_ptr<Context>& context){
  std::cout<<"Input label: ";
  std::string label;
  std::getline(std::cin, label);
  if (label.empty()){
    std::cout<<"label must be non-empty.\n";
    return StateOperationResult::INCORRECT_INPUT;
  }
  context->buffer_.label = label;
  return StateOperationResult::SUCCESS;
}