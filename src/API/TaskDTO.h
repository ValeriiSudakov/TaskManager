//
// Created by R2D2 on 29.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKDTO_H_
#define TASKMANAGER_SRC_TASKDTO_H_
#include "Memory Model/Task.h"
#include "Memory Model/TaskID.h"
class TaskDTO {
 public:
  Task task_;
  bool taskComplete_;
  TaskID taskID_;

 public:
  TaskDTO();
  TaskDTO(const Task& task, const bool& complete, const TaskID& id);
};

#endif //TASKMANAGER_SRC_TASKDTO_H_
