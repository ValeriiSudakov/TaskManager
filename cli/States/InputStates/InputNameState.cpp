//
// Created by valeriisudakov on 21.08.20.
//

#include "InputNameState.h"

InputNameState::InputNameState(): State(StatesID::InputName){}

InputNameState::~InputNameState() = default;

StateOperationResult InputNameState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO){
  std::string output { "Input name: " };
  IO.Output(output);

  std::string name { IO.Input() };

  if (name.empty()){
    std::string emptyNameError { "name must be non-empty.\n"};
    IO.Output(emptyNameError);
    return StateOperationResult::INCORRECT_INPUT;
  }

  context->buffer_.name = name;
  return StateOperationResult::SUCCESS;
}
