//
// Created by valeriisudakov on 21.08.20.
//

#include "InputNameState.h"

InputNameState::InputNameState(): State(StatesID::InputName){}

InputNameState::~InputNameState() = default;

StateOperationResult InputNameState::Do(const std::shared_ptr<Context>& context, const InputOutputLayer& io){
  std::string output { "Input name: " };
  io.Output(output);

  std::string name {io.Input() };

  if (name.empty()){
    std::string emptyNameError { "name must be non-empty.\n"};
    io.Output(emptyNameError);
    return StateOperationResult::INCORRECT_INPUT;
  }

  context->buffer_.name = name;
  return StateOperationResult::SUCCESS;
}
