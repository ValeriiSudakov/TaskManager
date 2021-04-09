//
// Created by valeriisudakov on 21.08.20.
//

#include "InputPriorityState.h"
#include "Priority.h"

InputPriorityState::InputPriorityState() : State(StatesID::INPUT_PRIORITY){}

InputPriorityState::~InputPriorityState() = default;


StateOperationResult InputPriorityState::Do(const std::shared_ptr<Context>& context, InputOutputLayer& io){

  std::string output { "Input task priority [first/1, second/2, third/3, none/0/" ": " };
  io.Output(output);

  std::string priorityStr {io.Input() };

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
    std::string incorrectPriorityError { "Incorrect input priority.\n" };
   io.Output(incorrectPriorityError);
    return StateOperationResult::INCORRECT_INPUT;
  }

  context->buffer_.priority = priority;
  return StateOperationResult::SUCCESS;
}
