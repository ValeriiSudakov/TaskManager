//
//
// Created by valerii.sudakov on 8/4/2020.


#include "TaskStorageClass.h"

TaskStorageClass::TaskStorageClass() = default;

std::optional<std::shared_ptr<TaskEntity>> TaskStorageClass::AddTask(const TaskEntity& task){
  auto newEntityTask = std::make_shared<TaskEntity>(task);
  tasks_.insert(std::make_pair(task.GetId(), newEntityTask));
  return newEntityTask;
}

const std::map<TaskID, std::shared_ptr<TaskEntity>>& TaskStorageClass::GetTasks() const {
  return tasks_;
}

std::optional<std::shared_ptr<TaskEntity>> TaskStorageClass::GetTask(const TaskID& taskID) const{
  auto task = tasks_.find(taskID);
  return (task == tasks_.end()) ? std::nullopt : std::make_optional(task->second);
}

bool TaskStorageClass::RemoveTask(const TaskID &id) {
  auto task = tasks_.find(id);
  if (task != tasks_.end()){
    task->second.reset();
    tasks_.erase(task);
    return true;
  }
  return false;
}


bool TaskStorageClass::PostponeTask(const TaskID& id, const Date& date){
  auto task = tasks_.find(id);
  if (task != tasks_.end()){
    auto result = task->second->PostponeDate(date);
    return result;
  }
  return false;
}