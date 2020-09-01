//
// Created by valeriisudakov on 21.08.20.
//

#include "InputDateState.h"

InputDateState::InputDateState() : State(StatesID::InputDate){}

InputDateState::~InputDateState() = default;

StateOperationResult InputDateState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO){
  std::string output {"Input date.\nUse current date - input 'now'.\nInput date format YYYY-MM-DD.\nInput: " };
  IO.Output(output);

  std::string dateStr { IO.Input() };

  Date date;
  if (dateStr == "now") {
    date = Date::GetCurrentTime();
  } else {
    try {
      date = Date(dateStr);
    } catch (const std::exception &ex) {
      std::string error { "Incorrect input date.\n" };
      IO.Output(error);
      return  StateOperationResult::INCORRECT_INPUT;
    }
  }

  context->buffer_.date = date;
  return  StateOperationResult::SUCCESS;
}
