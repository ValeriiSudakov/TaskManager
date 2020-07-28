//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKENTITY_H_
#define TASKMANAGER_SRC_TASKENTITY_H_
#include "Task.h"
#include "TaskID.h"
#include <memory>
#include <vector>

class TaskEntity {
 public:
  TaskEntity(const Task& task,TaskID id);
  ~TaskEntity();

 public:
  bool                          IsComplete() const;

  const TaskID                  GetId() const;
  const std::string             GetTaskLabel() const;
  const Task::Priority          GetTaskPriority() const;
  const std::string             GetTaskName() const;
  const Task                    GetTask() const;
  tm                            GetTaskDueDate() const;

 public:
  void                          AddSubtasks(std::weak_ptr<TaskEntity> subtask);
  void                          SetComplete();

 private:
  Task                                   task;
  TaskID                                 ID;
  bool                                   complete;
  std::vector<std::weak_ptr<TaskEntity>> subtasks;
};

#endif //TASKMANAGER_SRC_TASKENTITY_H_
