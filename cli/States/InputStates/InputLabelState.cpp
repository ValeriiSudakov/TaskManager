//
// Created by valeriisudakov on 21.08.20.
//

#include "InputLabelState.h"

InputLabelState::InputLabelState() : State(StatesID::InputLabel){}

InputLabelState::~InputLabelState() = default;

StateOperationResult InputLabelState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO){
  std::string output {"Input label: " };
  IO.Output(output);

  std::string labelStr { IO.Input() };

  if (labelStr.empty()){
    std::string emptyLabelError { "label must be non-empty.\n" };
    IO.Output(emptyLabelError);
    return StateOperationResult::INCORRECT_INPUT;
  }

  context->buffer_.label = labelStr;
  return StateOperationResult::SUCCESS;
}