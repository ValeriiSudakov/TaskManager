//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASK_H_
#define TASKMANAGER_SRC_TASK_H_
#include <iostream>
#include <ctime>
#include <optional>
#include "Date/Date.h"
#include "Priority.h"

class Task {

public:
  static std::optional<Task>  Create(const std::string &name, const std::string &label, Priority priority, const Date& dueDate);
  Task(const Task& task);

 public:
  const std::string          GetName() const;
  const std::string          GetLabel() const;
  const Priority             GetPriority() const;
  const Date                 GetDueDate() const;

 private:
  std::string   name_;
  std::string   label_;
  Priority      priority_;
  Date          dueDate_;

 private:
  Task(const std::string &name, const std::string &label, Priority priority, const Date& dueDate);
};

#endif //TASKMANAGER_SRC_TASK_H_
