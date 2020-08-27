//
// Created by valeriisudakov on 21.08.20.
//

#include "InputDateState.h"

InputDateState::InputDateState() = default;

InputDateState::~InputDateState() = default;

bool InputDateState::Do(const std::shared_ptr<Context>& context){
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
      return false;
    }
  }
  context->buffer_.date = date;
  return true;
}
