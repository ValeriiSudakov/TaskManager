//
// Created by R2D2 on 15.07.2020.
//

#include "TaskEntity.h"
#include <exception>

TaskEntity::TaskEntity(const Task& task, TaskID ID)
    : task_(task), id_(ID), complete_(false) {}

TaskEntity::~TaskEntity() = default;


const TaskID TaskEntity::GetId() const {
  return id_;
}

bool TaskEntity::IsComplete() const {
  return complete_;
}

void TaskEntity::SetComplete() {
  complete_ = true;
}

const std::string TaskEntity::GetTaskLabel() const{
  return task_.GetLabel();
}


const Task::Priority TaskEntity::GetTaskPriority() const {
  return task_.GetPriority();
}

Date TaskEntity::GetTaskDueDate() const{
  return task_.GetDueDate();
}

const std::string TaskEntity::GetTaskName() const{
  return task_.GetName();
}

const Task TaskEntity::GetTask() const {
  return task_;
}


void TaskEntity::AddSubtasks(std::weak_ptr<TaskEntity> subtask) {
    subtasks_.push_back(subtask);
}