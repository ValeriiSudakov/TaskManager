//
// Created by valeriisudakov on 21.08.20.
//

#include "InputLabelState.h"

InputLabelState::InputLabelState() : State(StatesID::INPUT_LABEL){}

InputLabelState::~InputLabelState() = default;

StateOperationResult InputLabelState::Do(const std::shared_ptr<Context>& context, const InputOutputLayer& io){
  std::string output {"Input label: " };
  io.Output(output);

  std::string labelStr {io.Input() };

  if (labelStr.empty()){
    std::string emptyLabelError { "label must be non-empty.\n" };
    io.Output(emptyLabelError);
    return StateOperationResult::INCORRECT_INPUT;
  }

  context->buffer_.label = labelStr;
  return StateOperationResult::SUCCESS;
}