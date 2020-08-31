//
//
// Created by valerii.sudakov on 8/4/2020.


#include "TaskStorage.h"

TaskStorage::TaskStorage() = default;

std::optional<std::shared_ptr<TaskEntity>> TaskStorage::AddTask(const Task& task){
  TaskID newTaskID = taskIDGenerate_.Generate();
  auto newEntityTask = std::make_shared<TaskEntity>(task, newTaskID);
  tasks_.insert(std::make_pair(newTaskID, newEntityTask));
  return newEntityTask;
}

std::optional<std::shared_ptr<TaskEntity>> TaskStorage::AddSubtask(const TaskID &rootTaskID, const Task &subtask) {

  auto task = tasks_.find(rootTaskID);
  if (task != tasks_.end()){ // if task exist
    TaskID newTaskID = taskIDGenerate_.Generate();
    auto newEntityTask = std::make_shared<TaskEntity>(subtask, TaskID(newTaskID), rootTaskID);

    task->second->AddSubtasks(newEntityTask);
    tasks_.insert(std::make_pair(newTaskID, newEntityTask));

    return newEntityTask;
  }

  return std::nullopt;
}

std::optional<std::shared_ptr<TaskEntity>> TaskStorage::GetTask(const TaskID& taskID) const{
  auto task = tasks_.find(taskID);
  return (task == tasks_.end()) ? std::nullopt : std::make_optional(task->second);
}
bool TaskStorage::RemoveTask(const TaskID &id) {
  auto task = tasks_.find(id);
  if (task != tasks_.end()){
    task->second.reset();
    tasks_.erase(task);
    return true;
  }
  return false;
}


bool TaskStorage::PostponeTask(const TaskID& id, const Date& date){
  auto task = tasks_.find(id);
  if (task != tasks_.end()){
    auto result = task->second->PostponeDate(date);
    return result;
  }
  return false;
}