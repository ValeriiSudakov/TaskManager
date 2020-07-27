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
  std::string newID = "t" + std::to_string(taskID.CreateID());
  auto newEntityTask = std::make_shared<TaskEntity>(task, newID);

  tasks.insert(std::make_pair(newID, newEntityTask));

  taskView.AddTask(newEntityTask);
}

void TaskService::AddSubtask(const std::string& rootTaskName, const Task& subtask,const Task::Priority& priority){
  std::string rootTaskID = GetTaskIDByName(rootTaskName);

  std::string newID = rootTaskID + "s" + std::to_string(taskID.CreateID());
  auto newEntityTask = std::make_shared<TaskEntity>(subtask, newID);
  tasks.insert(std::make_pair(newID, newEntityTask));

  taskView.AddTask(newEntityTask);
}

void TaskService::RemoveTask(const std::string& taskName){
  std::string taskID = GetTaskIDByName(taskName);
  RemoveTaskFromTasks(taskID);      //shared_ptr to task
  taskView.RemoveTask(taskID);
}

void TaskService::SetTaskComplete(const std::string& taskName){
  std::string taskID = GetTaskIDByName(taskName);
  // find root task
  auto i = tasks.find(taskID);
  while (i!=tasks.end()){
    // find all subtasks of this task
    if (i->first.find(taskID) != std::string::npos){
      i->second->SetComplete();
      ++i;
    } else break;
  }
}

void TaskService::RemoveTaskFromTasks(const std::string& taskID){

  std::vector<std::map<std::string, std::shared_ptr<TaskEntity>>::iterator> toDelete;
  // find root task to remove
  auto i = tasks.find(taskID);
  while (i!=tasks.end()){
    // find all subtasks of this task
    if (i->first.find(taskID) != std::string::npos){
      toDelete.push_back(i);
      ++i;
    } else break;
  }
  for (auto & i : toDelete){
    tasks.erase(i);
  }
}

void TaskService::PostponeDate(const std::string& taskName, const tm& postponeDate){
  std::string taskID = GetTaskIDByName(taskName);

  auto taskInfo = tasks[taskID];
  tasks[taskID]->SetTask(Task::Create(taskInfo->GetTaskName(), taskInfo->GetTaskLabel(),
                                                taskInfo->GetTaskPriority(), postponeDate));
}


const std::string& TaskService::GetTaskIDByName(const std::string& name) const{
  for (auto const& taskInfo : tasks) {
    if (taskInfo.second->GetTaskName() == name){
      return taskInfo.first;
    }
  }
  throw std::runtime_error{"Task not found"};
}

