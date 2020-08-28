//
// Created by valeriisudakov on 21.08.20.
//

#include "InputPriorityState.h"

InputPriorityState::InputPriorityState() {
  stateID_ = StatesID::InputPriority;
}

InputPriorityState::~InputPriorityState() = default;

StateOperationResult InputPriorityState::Do(const std::shared_ptr<Context>& context){
  std::cout<<"Input task priority [first/1, second/2, third/3, none/0/" ": ";
  std::string priorityStr;
  std::getline(std::cin, priorityStr);
  Priority priority;
  if (priorityStr == "first" || priorityStr == "1") {
    priority = Priority::FIRST;
  } else if (priorityStr == "second" || priorityStr == "2") {
    priority = Priority::SECOND;
  } else if (priorityStr == "third" || priorityStr == "3") {
    priority = Priority::THIRD;
  } else if (priorityStr == "none" || priorityStr == "0" || priorityStr == "") {
    priority = Priority::NONE;
  } else {
    std::cout<<"Incorrect input priority.\n";
    return StateOperationResult::INCORRECT_INPUT;
  }
  context->buffer_.priority = priority;
  return StateOperationResult::SUCCESS;
}
