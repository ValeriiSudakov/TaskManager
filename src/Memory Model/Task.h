//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASK_H_
#define TASKMANAGER_SRC_TASK_H_
#include <iostream>
#include <ctime>
#include <optional>

class Task {
 public:
  enum class Priority{
    FIRST = 1,
    SECOND,
    THIRD,
    NONE
  };

  static std::optional<Task>  Create(const std::string &name, const std::string &label, Priority priority, const tm &dueDate);

 public:
  Task(const Task& task);

 public:
  std::string    GetLabel() const;
  Priority       GetPriority() const;
  tm             GetDueDate() const;
  std::string    GetName() const;

 private:
  std::string   name_;
  std::string   label_;
  Priority      priority_;
  tm            dueDate_;

 private:
  Task(const std::string &name, const std::string &label, Priority priority, const tm &dueDate);
};

#endif //TASKMANAGER_SRC_TASK_H_
