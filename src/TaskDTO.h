//
// Created by R2D2 on 29.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKDTO_H_
#define TASKMANAGER_SRC_TASKDTO_H_
#include "Task.h"
#include "TaskID.h"
class TaskDTO {
 public:
  Task task;
  bool taskComplete;
  TaskID taskID;

 public:
  TaskDTO();
  TaskDTO(const Task& task, const bool& complete, const TaskID& id);
};

#endif //TASKMANAGER_SRC_TASKDTO_H_
