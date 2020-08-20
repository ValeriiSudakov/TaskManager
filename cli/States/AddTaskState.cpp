//
// Created by valeriisudakov on 18.08.20.
//

#include "AddTaskState.h"
#include "CorrectInput.h"

AddTaskState::AddTaskState() {
  stateName_ = "add task";
  nextStates_.insert("base");
  nextStates_.insert("exit");
}

AddTaskState::~AddTaskState() = default;

void AddTaskState::Do(Context& context){
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
  context.taskService_->AddTask(TaskDTO::Create(name.value(), label.value(), priority.value(), date.value()));
}
