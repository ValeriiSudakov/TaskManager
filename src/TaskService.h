//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKSERVICE_H_
#define TASKMANAGER_SRC_TASKSERVICE_H_
#include "TaskID.h"
#include "TaskEntity.h"
#include "Date.h"
#include "TaskOutput.h"
#include "TaskView.h"
#include <map>

class TaskService {
 public:
  TaskOutput taskOutput;

 public:
  TaskService();
  ~TaskService();

 public:
  void                  AddTask(const Task& task, const Task::Priority& priority);
  void                  AddSubtask(const TaskID& rootTaskName, const Task& subtask, const Task::Priority& priority);
  void                  SetTaskComplete(const TaskID& taskName);
  void                  RemoveTask(const std::string& taskName);
  void                  PostponeDate(const std::string& taskName, const tm& postponeDate);

  std::shared_ptr<TaskEntity>     GetTaskByName(const std::string& name) const; //for test

 private:
  void                            RemoveTaskFromTasks(const TaskID& taskID);
  const TaskID&                   GetTaskIDByName(const std::string& name) const;

 private:
  std::map<unsigned int, std::shared_ptr<TaskEntity>>       tasks;
  TaskView                                                  taskView;
  TaskID                                                    taskID;
};

#endif //TASKMANAGER_SRC_TASKSERVICE_H_
