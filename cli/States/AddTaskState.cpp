//
// Created by valeriisudakov on 18.08.20.
//

#include "AddTaskState.h"

AddTaskState::AddTaskState() {
  stateName_ = "add task";
  nextStates_.insert("base");
  nextStates_.insert("exit");
}

AddTaskState::~AddTaskState() = default;

void AddTaskState::Do(Context& context){
  std::cout<<"Input task name: ";
  std::string name;
  std::getline(std::cin, name);
  if (name.empty()){
    std::cout<<"Name must be non-empty.\n";
    return;
  }

  std::cout<<"Input task label: ";
  std::string label;
  std::getline(std::cin, label);
  if (label.empty()){
    std::cout<<"Label must be non-empty.\n";
    return;
  }

  std::cout<<"Input task priority [first/1, second/2, third/3, none/0/" ": ";
  std::string priorityStr;
  std::getline(std::cin, priorityStr);
  Priority priority;
  if (priorityStr == "first" || priorityStr == "1"){
    priority = Priority::FIRST;
  } else if (priorityStr == "second" || priorityStr == "2"){
    priority = Priority::SECOND;
  } else if (priorityStr == "third" || priorityStr == "3"){
    priority = Priority::THIRD;
  } else if (priorityStr == "none" || priorityStr == "0" || priorityStr == ""){
    priority = Priority::NONE;
  }else {
    std::cout<<"Incorrect input priority.\n";
    return;
  }

  std::cout<<"Input date as : year-mon-date.\nSet current date: now.\nInput: ";
  std::string dateStr;
  std::getline(std::cin, dateStr);
  Date date;
  if (dateStr == "now"){
    date = Date::GetCurrentTime();
  } else {
    try {
      date = Date(dateStr);
    } catch (const std::exception& ex) {
      std::cout<<"Incorrect input date.\n";
      std::cout<<ex.what()<<std::endl;
      return;
    }
  }
  context.taskService_->AddTask(TaskDTO::Create(name, label, priority, date));
}
