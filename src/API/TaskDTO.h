//
// Created by R2D2 on 29.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKDTO_H_
#define TASKMANAGER_SRC_TASKDTO_H_
#include "Memory Model/Task.h"
#include "Memory Model/TaskID.h"
class TaskDTO {
 public:
  TaskDTO();
  TaskDTO(const Task& task, const bool& complete, const TaskID& id);
  const Task &GetTask() const;
  bool IsTaskComplete() const;
  const TaskID &GetTaskId() const;

 private:
  Task task_;
  bool taskComplete_;
  TaskID taskID_;
};

#endif //TASKMANAGER_SRC_TASKDTO_H_
