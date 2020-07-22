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

void TaskService::RemoveTask(const std::string& taskID){
  RemoveTaskFromByPriority(taskID); //weak_ptr to task
  RemoveTaskFromTasks(taskID);      //shared_ptr to task
}

void TaskService::RemoveTaskFromTasks(const std::string& taskID){
  std::vector<std::map<std::string, std::shared_ptr<TaskEntity>>::iterator> toDelete;
  // find task to delete
  auto i = tasks.find(taskID);
  while (i!=tasks.end()){
    // find all subtasks of this task
    if (i->first.find(taskID) != std::string::npos){
      toDelete.push_back(i);
      ++i;
    } else break;
  }
  for (int i = 0; i < toDelete.size();++i){
    tasks.erase(toDelete[i]);
  }
}

void TaskService::RemoveTaskFromByPriority(const std::string& taskID){
  std::vector<std::multimap<Task::Priority, std::weak_ptr<TaskEntity>>::iterator> toDelete;
  for (auto i = byPriority.begin(); i != byPriority.end(); ++i){
    if (i->second.lock()->GetId().find(taskID) != std::string::npos){
      toDelete.push_back(i);
    }
  }
  if (toDelete.empty()){
    throw std::runtime_error{"task not found"};
  }
  for (int i = 0; i < toDelete.size();++i){
    byPriority.erase(toDelete[i]);
  }
}


const std::string& TaskService::GetTaskIDByName(const std::string& name) const{
  for (auto const& taskInfo : tasks) {
    if (taskInfo.second->GetTaskName() == name){
      return taskInfo.first;
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
  TaskOutput to;
  if (SortedByPrioriry){
    for (auto const& [key, val] : byPriority) {
      if (Date::IsToday(val.lock()->GetTaskDueDate())){
        to.Print(*val.lock()->GetTask());
      }
    }
  } else {
    for (auto const& [key, val] : tasks){
      if (Date::IsToday(val->GetTaskDueDate())){
        to.Print(*val->GetTask());
      }
    }
  }
}

void TaskService::ShowAllWeekTasks(bool SortedByPrioriry){
  TaskOutput to;
  if (SortedByPrioriry){
    for (auto const& [key, val] : byPriority) {
      if (Date::IsThisWeek(val.lock()->GetTaskDueDate())){
        to.Print(*val.lock()->GetTask());
      }
    }
  } else {
    for (auto const& [key, val] : tasks){
      if (Date::IsThisWeek(val->GetTaskDueDate())){
        to.Print(*val->GetTask());
      }
    }
  }
}

void TaskService::ShowAllTaskByLabel(std::string label, bool SortedByPrioriry){
  TaskOutput to;
  if (SortedByPrioriry){
    for (auto const& [key, val] : byPriority) {
      if (val.lock()->GetTaskLabel() == label){
        to.Print(*val.lock()->GetTask());
      }
    }
  } else {
    for (auto const& [key, val] : tasks){
      if (val->GetTaskLabel() == label){
        to.Print(*val->GetTask());
      }
    }
  }
}