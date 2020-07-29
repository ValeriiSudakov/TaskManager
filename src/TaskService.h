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
  TaskOutput  taskOutput;
  TaskView    taskView;
 public:
  TaskService();
  ~TaskService();

 public:
  void                      AddTask(const Task& task, const Task::Priority& priority);
  bool                      AddSubtask(const TaskID& rootTaskID, const Task& subtask, const Task::Priority& priority);

 private:
  std::map<unsigned int, std::shared_ptr<TaskEntity>>       tasks;
  TaskID                                                    taskID;
};

#endif //TASKMANAGER_SRC_TASKSERVICE_H_
