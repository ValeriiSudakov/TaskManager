//
// Created by R2D2 on 31.07.2020.
//

#include "TaskRepository.h"
TaskRepository::TaskRepository() : taskIDGenerate_(TaskIDGenerate()) {}
TaskRepository::~TaskRepository() = default;


std::weak_ptr<TaskEntity> TaskRepository::AddTask(const Task& task, const Task::Priority& priority){
  TaskID newTaskID = taskIDGenerate_.Generate();
  auto newEntityTask = std::make_shared<TaskEntity>(task, newTaskID);
  tasks_.insert(std::make_pair(newTaskID.GetID(), newEntityTask));
  return newEntityTask;
}

std::optional<std::weak_ptr<TaskEntity>> TaskRepository::AddSubtask(const TaskID &rootTaskID, const Task &subtask,
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
