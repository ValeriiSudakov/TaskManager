//
// Created by valeriisudakov on 21.08.20.
//

#include "InputDateState.h"

InputDateState::InputDateState(std::shared_ptr<State> nextState) : nextState_(std::move(nextState)) {
  stateName_ = "input date";
  fail = false;
}

InputDateState::~InputDateState() = default;

void InputDateState::Do(Context& context){
  std::cout<<"Input date.\nUse current date - input 'now'.\nInput date format YYYY-MM-DD.\nInput: ";
  std::string dateStr;
  std::getline(std::cin, dateStr);
  Date date;
  if (dateStr == "now") {
    date = Date::GetCurrentTime();
  } else {
    try {
      date = Date(dateStr);
    } catch (const std::exception &ex) {
      std::cout<<"Incorrect input date.\n";
      fail = true;
    }
  }
  context.buffer_.date = date;
}

std::shared_ptr<State> InputDateState::ReadAction() {
  return fail ? std::make_shared<InputDateState>(std::move(nextState_)) : std::move(nextState_);
}
