//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKENTITY_H_
#define TASKMANAGER_SRC_TASKENTITY_H_
#include "Task.h"
#include "TaskID.h"
#include <memory>

class TaskEntity {
 public:
  TaskEntity(const Task& task,std::string id);
  TaskEntity(const TaskEntity&) = delete;
  ~TaskEntity();

 public:
  bool                          IsComplete() const;

  const std::string             GetId() const;
  const std::string             GetTaskLabel() const;
  const Task::Priority          GetTaskPriority() const;
  const std::string             GetTaskName() const;
  const Task                    GetTask() const;
  tm                            GetTaskDueDate() const;

  void                          SetComplete();
  void                          SetTask(const Task& newTask);
 private:
  Task                    task;
  std::string             ID;
  bool                    complete;
};

#endif //TASKMANAGER_SRC_TASKENTITY_H_
