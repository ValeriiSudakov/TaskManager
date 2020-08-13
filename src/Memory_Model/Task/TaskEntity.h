//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKENTITY_H_
#define TASKMANAGER_SRC_TASKENTITY_H_
#include "Task.h"
#include "API/TaskID.h"
#include <memory>
#include <map>

class TaskEntity {
 public:
  TaskEntity(const Task& task,TaskID ID);
  TaskEntity(const Task& task,TaskID ID, TaskID parentID);
  ~TaskEntity();

 public:
  bool                                                      IsComplete() const;
  bool                                                      RemoveTaskFromSubtasks(const TaskID& id);
  bool                                                      PostponeDate(const Date& newDate);

  const TaskID                                              GetId() const;
  const TaskID                                              GetParentId() const;
  const std::string                                         GetLabel() const;
  const Priority                                            GetPriority() const;
  const std::string                                         GetName() const;
  const Task                                                GetTask() const;
  const Date                                                GetDueDate() const;
  const std::map<TaskID, std::weak_ptr<TaskEntity>>         GetSubtasks() const;

 public:
  void                                                      AddSubtasks(std::weak_ptr<TaskEntity> subtask);
  void                                                      SetComplete();

 private:
  Task                                                  task_;
  TaskID                                                id_;
  TaskID                                                parentID_;
  bool                                                  complete_;
  std::map<TaskID, std::weak_ptr<TaskEntity>>           subtasks_;
};

#endif //TASKMANAGER_SRC_TASKENTITY_H_
