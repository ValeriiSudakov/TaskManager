//
// Created by R2D2 on 17.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKOUTPUT_H_
#define TASKMANAGER_SRC_TASKOUTPUT_H_
#include "TaskEntity.h"
#include "TaskDTO.h"
#include <vector>

class TaskOutput {
 public:
  TaskOutput();
  ~TaskOutput();
 public:
  void Print(const std::vector<TaskDTO>& tasks) const;
 private:
  const std::string   GetTaskPriorityStr(const Task::Priority& priority) const;

};

#endif //TASKMANAGER_SRC_TASKOUTPUT_H_
