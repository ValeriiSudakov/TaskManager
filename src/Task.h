//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASK_H_
#define TASKMANAGER_SRC_TASK_H_
#include <iostream>
#include <ctime>

class Task {
 public:
  enum class Priority{
    HIGH = 1,
    LOW,
    NONE
  };

  // в срр
  static Task          Create(const std::string &name, const std::string &label, Priority priority, const tm &dueDate);

 public:
  ~Task();
  Task(const Task& task);
 public:

  // убрать конст ссылка
  const std::string&   GetLabel() const;
  Priority             GetPriority() const;
  const tm&            GetDueDate() const;
  const std::string&   GetName() const;
 private:
  std::string   name;
  std::string   label;
  Priority      priority;
  tm            dueDate;

 private:
  Task(const std::string &name, const std::string &label, Priority priority, const tm &dueDate);
};

#endif //TASKMANAGER_SRC_TASK_H_
