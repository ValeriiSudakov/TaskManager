//
// Created by valeriisudakov on 20.08.20.
//

#include "AddSubtaskState.h"
#include "CorrectInput.h"

AddSubtaskState::AddSubtaskState() {
  stateName_ = "add subtask";
  nextStates_.insert("base");
  nextStates_.insert("exit");
}

AddSubtaskState::~AddSubtaskState() = default;

void AddSubtaskState::Do(Context& context) {
  std::cout<<"Input number of task to add subtask: ";
  auto number = CorrectInput::Number();
  if (!number.has_value()){
    std::cout<<"Incorrect input number.\n";
    return;
  }

  std::cout<<"Input task name: ";
  auto name = CorrectInput::Name();
  if (!name.has_value()){
    std::cout<<"Name must be non-empty.\n";
    return;
  }

  std::cout<<"Input task label: ";
  auto label = CorrectInput::Label();
  if (!label.has_value()){
    std::cout<<"Label must be non-empty.\n";
    return;
  }

  std::cout<<"Input task priority [first/1, second/2, third/3, none/0/" ": ";
  auto priority = CorrectInput::Priority();
  if (!priority.has_value()){
    std::cout<<"Incorrect input priority.\n";
    return;
  }

  std::cout<<"Input date as : year-mon-date.\nSet current date: now.\nInput: ";
  auto date = CorrectInput::Date();
  if (!date.has_value()){
    std::cout<<"Incorrect input date.\n";
    return;
  }
}
