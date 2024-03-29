//
// Created by valeriisudakov on 21.08.20.
//

#include "InputDateState.h"
#include "Date.h"

InputDateState::InputDateState() : State(StatesID::INPUT_DATE){}

InputDateState::~InputDateState() = default;

StateOperationResult InputDateState::Do(const std::shared_ptr<Context>& context, InputOutputLayer& io){
  std::string output {"Input date.\nUse current date - input 'now'.\nInput date format YYYY-MM-DD.\nInput: " };
  io.Output(output);

  std::string dateStr {io.Input() };

  Date date;
  if (dateStr == "now") {
    date = Date::GetCurrentTime();
  } else {
    try {
      date = Date(dateStr);
    } catch (const std::exception &ex) {
      std::string error { "Incorrect input date.\n" };
      io.Output(error);
      return  StateOperationResult::INCORRECT_INPUT;
    }
  }

  context->buffer_.date = date;
  return  StateOperationResult::SUCCESS;
}
