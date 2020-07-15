//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKENTITY_H_
#define TASKMANAGER_SRC_TASKENTITY_H_
#include "Task.h"
#include <memory>

class TaskEntity {
 public:
  TaskEntity(const std::shared_ptr<Task> &task, unsigned int id);
  ~TaskEntity();

 public:
  unsigned int GetId() const;
  bool IsComplete() const;
  const std::string GetTaskLabel() const;
  const std::string GetTaskPriorityStr() const;
  const Task::Priority GetTaskPriority() const;
  const std::string GetTaskName() const;
  tm GetTaskDueDate() const;
  void SetComplete();
  void PrintTaskDueDate() const;

 private:
  std::shared_ptr<Task> task;
  unsigned int ID;
  bool complete;

 private:
  TaskEntity(const TaskEntity&);
  void operator=(const TaskEntity&);


};

#endif //TASKMANAGER_SRC_TASKENTITY_H_
