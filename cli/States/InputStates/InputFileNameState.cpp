//
// Created by valeriisudakov on 12.10.20.
//

#include "InputFileNameState.h"

InputFileNameState::InputFileNameState() : State(StatesID::INPUT_FILE_NAME){}

InputFileNameState::~InputFileNameState() = default;

StateOperationResult InputFileNameState::Do(const std::shared_ptr<Context>& context, InputOutputLayer& io){
  std::string output {"Input file name: " };
  io.Output(output);

  std::string fileNameStr {io.Input() };

  if (fileNameStr.empty()){
    std::string emptyLabelError { "file name must be non-empty.\n" };
    io.Output(emptyLabelError);
    return StateOperationResult::INCORRECT_INPUT;
  }

  context->buffer_.fileName = fileNameStr;
  return StateOperationResult::SUCCESS;
}