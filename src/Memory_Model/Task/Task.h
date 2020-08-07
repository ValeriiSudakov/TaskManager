//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASK_H_
#define TASKMANAGER_SRC_TASK_H_
#include <iostream>
#include <ctime>
#include <optional>
#include "Memory_Model/Date/Date.h"

class Task {
 public:
  enum class Priority{
    FIRST = 1,
    SECOND,
    THIRD,
    NONE
  };
  static std::optional<Task>  Create(const std::string &name, const std::string &label, Priority priority, const Date& dueDate);

 public:
  Task(const Task& task);

 public:
  std::string    GetLabel() const;
  Priority       GetPriority() const;
  Date           GetDueDate() const;
  std::string    GetName() const;

 private:
  std::string   name_;
  std::string   label_;
  Priority      priority_;
  Date          dueDate_;

 private:
  Task(const std::string &name, const std::string &label, Priority priority, const Date& dueDate);
};

#endif //TASKMANAGER_SRC_TASK_H_
