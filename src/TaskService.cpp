//
// Created by R2D2 on 15.07.2020.
//

#include "TaskService.h"
#include "TaskOutput.h"
#include <string>
#include <vector>

TaskService::TaskService() : taskID(){}
TaskService::~TaskService() = default;

std::shared_ptr<TaskEntity> TaskService::GetTaskByName(const std::string& name) const {
    for (const auto& taskInfo : tasks){
      if (taskInfo.second->GetTaskName() == name){
        return taskInfo.second;
      }
    }
  throw std::runtime_error{"Task not found"};
}

void TaskService::AddTask(const Task& task, const Task::Priority& priority){
  auto newEntityTask = std::make_shared<TaskEntity>(task, TaskID(taskID.GenerateID()));
  tasks.insert(std::make_pair(taskID.GenerateID(), newEntityTask));
  taskView.AddTask(newEntityTask);
}

void TaskService::AddSubtask(const TaskID& rootTaskName, const Task& subtask,const Task::Priority& priority){
  auto newEntityTask = std::make_shared<TaskEntity>(subtask, TaskID(taskID.GenerateID()));
  tasks.insert(std::make_pair(taskID.GenerateID(), newEntityTask));
  taskView.AddTask(newEntityTask);
}

void TaskService::RemoveTask(const std::string& taskName){

}

void TaskService::SetTaskComplete(const TaskID& taskID){

}

void TaskService::RemoveTaskFromTasks(const TaskID& taskID){

}

void TaskService::PostponeDate(const std::string& taskName, const tm& postponeDate){

}


const TaskID& TaskService::GetTaskIDByName(const std::string& name) const{
  for (auto const& taskInfo : tasks) {
    if (taskInfo.second->GetTaskName() == name){
      return taskInfo.first;
    }
  }
  throw std::runtime_error{"Task not found"};
}

