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
  TaskEntity(const Task& task,TaskID ID);
  TaskEntity(const Task& task,TaskID ID, TaskID parentID);
  ~TaskEntity();

 public:
  bool                                          IsComplete() const;

  const TaskID                                  GetId() const;
  const TaskID                                  GetParentId() const;
  const std::string                             GetTaskLabel() const;
  const Task::Priority                          GetTaskPriority() const;
  const std::string                             GetTaskName() const;
  const Task                                    GetTask() const;
  const Date                                    GetTaskDueDate() const;
  const std::vector<std::weak_ptr<TaskEntity>>  GetSubtasks() const;

 public:
  void                                          AddSubtasks(std::weak_ptr<TaskEntity> subtask);
  void                                          SetComplete();

 private:
  Task                                   task_;
  TaskID                                 id_;
  TaskID                                 parentID_;
  bool                                   complete_;
  std::vector<std::weak_ptr<TaskEntity>> subtasks_;
};

#endif //TASKMANAGER_SRC_TASKENTITY_H_
