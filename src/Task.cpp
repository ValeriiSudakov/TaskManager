//
// Created by R2D2 on 15.07.2020.
//

#include "Task.h"
Task::Task(const std::string &name, const std::string &label, Task::Priority priority, const tm &dueDate)
    : name_(name), label_(label), priority_(priority), dueDate_(dueDate) {}

Task::Task(const Task& task)
    : name_(task.name_), label_(task.label_), priority_(task.priority_), dueDate_(task.dueDate_){}

Task::Task(){}

Task::~Task() = default;

Task Task::Create(const std::string &name, const std::string &label, Priority priority, const tm &dueDate){
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
