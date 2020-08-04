//
// Created by valerii.sudakov on 8/4/2020.
//

#include "TaskStorage.h"


std::shared_ptr<TaskEntity> TaskStorage::AddTask(const Task& task, const Task::Priority& priority){
  TaskID newTaskID = taskIDGenerate_.Generate();
  auto newEntityTask = std::make_shared<TaskEntity>(task, newTaskID);
  tasks_.insert(std::make_pair(newTaskID.GetID(), newEntityTask));
  return newEntityTask;
}

std::optional<std::shared_ptr<TaskEntity>> TaskStorage::AddSubtask(const TaskID &rootTaskID, const Task &subtask,
                                const Task::Priority &priority) {

  if (tasks_.find(rootTaskID.GetID()) != tasks_.end()){ // if task exist
    TaskID newTaskID = taskIDGenerate_.Generate();
    auto newEntityTask = std::make_shared<TaskEntity>(subtask, TaskID(newTaskID));

    tasks_[rootTaskID.GetID()]->AddSubtasks(newEntityTask);
    tasks_.insert(std::make_pair(newTaskID.GetID(), newEntityTask));

    return newEntityTask;
  }
  return std::nullopt;
}
std::optional<std::shared_ptr<TaskEntity>> TaskStorage::GetTask(const TaskID& taskID){
  if (tasks_.find(taskID.GetID()) == tasks_.end()){
    return std::nullopt;
  }
  return tasks_[taskID.GetID()];
}
