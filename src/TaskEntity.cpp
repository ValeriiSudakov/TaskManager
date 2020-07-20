//
// Created by R2D2 on 15.07.2020.
//

#include "TaskEntity.h"
#include <exception>

TaskEntity::TaskEntity(const std::shared_ptr<Task> &task, std::string id)
    : task(task), ID(id), complete(false) {}

TaskEntity::~TaskEntity() = default;

TaskEntity::TaskEntity(const TaskEntity&){ }

void TaskEntity::operator=(const TaskEntity&){ }


const std::string TaskEntity::GetId() const {
  return ID;
}

bool TaskEntity::IsComplete() const {
  return complete;
}

void TaskEntity::SetComplete() {
  complete = true;
}

const std::string TaskEntity::GetTaskLabel() const{
  return task->GetLabel();
}


const Task::Priority TaskEntity::GetTaskPriority() const {
  return task->GetPriority();
}

tm TaskEntity::GetTaskDueDate() const{
  return task->GetDueDate();
}

const std::string TaskEntity::GetTaskName() const{
  return task->GetName();
}

const std::shared_ptr<Task> &TaskEntity::GetTask() const {
  return task;
}

