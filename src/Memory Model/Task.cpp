//
// Created by R2D2 on 15.07.2020.
//

#include "Task.h"
#include "Date.h"

Task::Task(const std::string &name, const std::string &label, Task::Priority priority, const tm &dueDate)
    : name_(name), label_(label), priority_(priority), dueDate_(dueDate) {}

Task::Task(const Task& task)
    : name_(task.name_), label_(task.label_), priority_(task.priority_), dueDate_(task.dueDate_){}

Task::Task(){}

Task::~Task() = default;

std::optional<Task> Task::Create(const std::string &name, const std::string &label, Priority priority, const tm &dueDate){
  if (name == ""){
    return std::nullopt;
  }
  if (label == ""){
    return std::nullopt;
  }
  tm currentDate = Date::GetCurrentTime();
  currentDate.tm_sec = 0;
  tm inputDate = dueDate;
  inputDate.tm_sec = 0;
  if (mktime(&inputDate) < mktime(&currentDate)){
    return std::nullopt;
  }
  return Task(name, label, priority, dueDate);
}

std::string Task::GetName() const {
  return name_;
}
std::string Task::GetLabel() const {
  return label_;
}
Task::Priority Task::GetPriority() const {
  return priority_;
}

tm Task::GetDueDate() const {
  return dueDate_;
}
