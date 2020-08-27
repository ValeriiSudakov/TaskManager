//
// Created by valeriisudakov on 21.08.20.
//

#include "InputNameState.h"

InputNameState::InputNameState() = default;

InputNameState::~InputNameState() = default;

bool InputNameState::Do(const std::shared_ptr<Context>& context){
  std::cout<<"Input name: ";
  std::string name;
  std::getline(std::cin, name);
  if (name.empty()){
    std::cout<<"name must be non-empty.\n";
    return false;
  }
  context->buffer_.name = name;
  return true;
}
