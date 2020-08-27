//
// Created by valeriisudakov on 21.08.20.
//

#include "InputLabelState.h"

InputLabelState::InputLabelState() = default;

InputLabelState::~InputLabelState() = default;

bool InputLabelState::Do(const std::shared_ptr<Context>& context){
  std::cout<<"Input label: ";
  std::string label;
  std::getline(std::cin, label);
  if (label.empty()){
    std::cout<<"label must be non-empty.\n";
    return false;
  }
  context->buffer_.label = label;
  return true;
}