//
// Created by valeriisudakov on 21.08.20.
//

#include "InputNameState.h"

InputNameState::InputNameState(): State(StatesID::InputName){}

InputNameState::~InputNameState() = default;

StateOperationResult InputNameState::Do(const std::shared_ptr<Context>& context){
  std::cout<<"Input name: ";
  std::string name;
  std::getline(std::cin, name);
  if (name.empty()){
    std::cout<<"name must be non-empty.\n";
    return StateOperationResult::INCORRECT_INPUT;
  }
  context->buffer_.name = name;
  return StateOperationResult::SUCCESS;
}
