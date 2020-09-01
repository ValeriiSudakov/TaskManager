//
// Created by valeriisudakov on 25.08.20.
//

#include "InputIDState.h"

InputIDState::InputIDState() : State(StatesID::InputID){}

InputIDState::~InputIDState() = default;

StateOperationResult InputIDState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO){
  std::string output {"Input ID: " };
  IO.Output(output);

  std::string idStr { IO.Input() };

  if (idStr.empty()){
    std::string emptyStrError { "ID must be non-empty.\n" };
    IO.Output(emptyStrError);
    return StateOperationResult::INCORRECT_INPUT;
  }
  if (idStr.find_first_not_of("0123456789") != std::string::npos){
    std::string strContainNumberError { "ID must contains only numbers!\n" };
    IO.Output(strContainNumberError);
    return StateOperationResult::INCORRECT_INPUT;
  }
  auto id = std::atoi(idStr.c_str());
  if (id > context->tasks_.size()-1){
    std::string idOutOfRangeError{ "ID out of tasks range.\n" };
    IO.Output(idOutOfRangeError);
    return StateOperationResult::INCORRECT_INPUT;
  }

  context->buffer_.id = context->tasks_[id].GetTaskId().Get();
  return StateOperationResult::SUCCESS;
}
