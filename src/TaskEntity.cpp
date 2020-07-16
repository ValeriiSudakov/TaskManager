//
// Created by R2D2 on 15.07.2020.
//

#include "TaskEntity.h"
TaskEntity::TaskEntity(const std::shared_ptr<Task> &task, const unsigned int id)
    : task(task), ID(id), complete(false) {}

TaskEntity::~TaskEntity() = default;

TaskEntity::TaskEntity(const TaskEntity&){ }

void TaskEntity::operator=(const TaskEntity&){ }


unsigned int TaskEntity::GetId() const {
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

const std::string TaskEntity::GetTaskPriorityStr() const{
  Task::Priority priority = task->GetPriority();
  if (priority == Task::Priority::HIGH){ return "High"; }
  else if (priority == Task::Priority::LOW){ return "Low"; }
  else if (priority == Task::Priority::NONE){ return "None"; }
  else return "";
}

const Task::Priority TaskEntity::GetTaskPriority() const {
  return task->GetPriority();
}

tm TaskEntity::GetTaskDueDate() const{
  return task->GetDueDate();
}

void TaskEntity::PrintTaskDueDate() const{
  tm date = task->GetDueDate();
  std::cout << "Year:"  << 1900 + date.tm_year << std::endl;
  std::cout << "Month: "<< 1 + date.tm_mon<< std::endl;
  std::cout << "Day: "  <<  date.tm_mday << std::endl;
  std::cout << "Time: " << 1 + date.tm_hour << ":"
                        << 1 + date.tm_min << ":"
                        << 1 + date.tm_sec << std::endl;
}
const std::string TaskEntity::GetTaskName() const{
  return task->GetName();
}
const std::shared_ptr<Task> &TaskEntity::GetTask() const {
  return task;
}

