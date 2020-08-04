//
// Created by R2D2 on 29.07.2020.
//

#include "TaskDTO.h"

TaskDTO::TaskDTO() {}

TaskDTO::TaskDTO(const Task& task, const bool& complete, const TaskID& id)
    : task_(task), taskComplete_(complete), taskID_(id) {}

const Task &TaskDTO::GetTask() const {
  return task_;
}
bool TaskDTO::IsTaskComplete() const {
  return taskComplete_;
}
const TaskID &TaskDTO::GetTaskId() const {
  return taskID_;
}
