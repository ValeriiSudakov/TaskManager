//
// Created by R2D2 on 15.07.2020.
//

#include "FullTask.h"
FullTask::FullTask(const std::shared_ptr<TaskEntity> &root_task) : rootTask(root_task) {}
FullTask::~FullTask() = default;

unsigned int FullTask::GetID() const{
  return rootTask->GetId();
}

void FullTask::AddSubtask(std::shared_ptr<TaskEntity>& root_task){
  subtasks.push_back(std::make_shared<FullTask>(FullTask(root_task)));
}

std::string FullTask::GetName() const{
  return rootTask->GetTaskName();
}

TaskEntity& FullTask::FindSubtask(unsigned int rootTaskID){
  for (auto task : subtasks){
    if(task->GetID() == rootTaskID){
      return *task->rootTask;
    } else if (!task->subtasks.empty()){
      FindSubtask(rootTaskID);
    }
  }
}

std::vector<std::shared_ptr<FullTask>> &FullTask::GetSubtasks() {
  return subtasks;
}