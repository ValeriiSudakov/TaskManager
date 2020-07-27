//
// Created by R2D2 on 15.07.2020.
//

#include "Task.h"
Task::Task(const std::string &name, const std::string &label, Task::Priority priority, const tm &dueDate)
    : name(name), label(label), priority(priority), dueDate(dueDate) {}

Task::Task(const Task& task)
    : name(task.name), label(task.label), priority(task.priority), dueDate(task.dueDate){}

Task::~Task() = default;

Task Task::Create(const std::string &name, const std::string &label, Priority priority, const tm &dueDate){
  return Task(name, label, priority, dueDate);
}

const std::string &Task::GetName() const {
  return name;
}
const std::string &Task::GetLabel() const {
  return label;
}
Task::Priority Task::GetPriority() const {
  return priority;
}

const tm &Task::GetDueDate() const {
  return dueDate;
}
