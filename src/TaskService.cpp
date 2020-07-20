//
// Created by R2D2 on 15.07.2020.
//

#include "TaskService.h"
#include "TaskOutput.h"
#include <string>

TaskService::TaskService() : taskID(){}
TaskService::~TaskService() = default;

std::shared_ptr<TaskEntity> TaskService::GetTaskByName(const std::string& name) const {
    std::shared_ptr<TaskEntity> sp;
    for (const auto& taskInfo : byPriority){
      sp = taskInfo.second.lock();
      if (sp->GetTaskName() == name){
        return sp;
      }
      sp.reset();
    }
  throw std::runtime_error{"Task not found"};
}

void TaskService::AddTask(const Task& task, const Task::Priority& priority){
  std::string newID = "t" + std::to_string(taskID.CreateID());
  auto newEntityTask = std::make_shared<TaskEntity>(std::make_shared<Task>(task), newID);

  tasks.insert(std::make_pair(newID, newEntityTask));
  byPriority.insert(std::make_pair(priority, newEntityTask));
}

void TaskService::AddSubtask(const std::string& rootTaskID, const Task& subtask,const Task::Priority& priority){
  std::string newID = rootTaskID + "s" + std::to_string(taskID.CreateID());
  auto newEntityTask = std::make_shared<TaskEntity>(std::make_shared<Task>(subtask), newID);
  tasks.insert(std::make_pair(newID, newEntityTask));
  byPriority.insert(std::make_pair(priority, newEntityTask));
}

const std::string& TaskService::GetTaskIDByName(const std::string& name) const{
  for (auto const& [key, val] : tasks) {
    if (val->GetTaskName() == name){
      return key;
    }
  }
  throw std::runtime_error{"Task not found"};
}


void TaskService::ShowAllTasks(bool SortedByPrioriry){
  TaskOutput to;
  if (SortedByPrioriry){
    for (auto const& [key, val] : byPriority) {
      to.Print(*val.lock()->GetTask());
    }
  } else {
    for (auto const& [key, val] : tasks){
      to.Print(*val->GetTask());
    }
  }

}

void TaskService::ShowAllTodayTasks(bool SortedByPrioriry){

}

void TaskService::ShowAllWeekTasks(bool SortedByPrioriry){

}

void TaskService::ShowAllTaskByLabel(std::string label, bool SortedByPrioriry){

}