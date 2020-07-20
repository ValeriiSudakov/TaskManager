//
// Created by R2D2 on 15.07.2020.
//

#include "FullTask.h"
FullTask::FullTask(const std::shared_ptr<TaskEntity> &root_task) : rootTask(root_task) {}
FullTask::~FullTask() {
  if (!subtasks.empty()){
    for (auto task : subtasks){
      task.reset();
    }
  }
}

unsigned int FullTask::GetID() const{
  return rootTask->GetId();
}

void FullTask::AddSubtask(std::weak_ptr<FullTask>& fullTask){
  subtasks.push_back(fullTask);
}

std::string FullTask::GetName() const{
  return rootTask->GetTaskName();
}

TaskEntity& FullTask::FindSubtask(unsigned int rootTaskID){
  std::shared_ptr<FullTask> sp;
  for (auto task : subtasks){
    sp = task.lock();
    if(sp->GetID() == rootTaskID){
      return *sp->rootTask;
    } else if (!sp->subtasks.empty()){
      FindSubtask(rootTaskID);
    }
    sp.reset();
  }
}

std::vector<std::weak_ptr<FullTask>> &FullTask::GetSubtasks() {
  return subtasks;
}
const std::shared_ptr<TaskEntity> &FullTask::GetRootTask() const {
  return rootTask;
}
