//
// Created by R2D2 on 15.07.2020.
//

#include "TaskService.h"
#include "TaskOutput.h"
#include <string>
#include <vector>

TaskService::TaskService() : taskID(){}
TaskService::~TaskService() = default;

std::weak_ptr<TaskEntity> TaskService::GetTaskByName(const std::string& name) const {
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
  byLabel.insert(std::make_pair(task.GetLabel(), newEntityTask));
  byName.insert(std::make_pair(task.GetName(), newEntityTask));
  tm taskDate = task.GetDueDate();
  time_t date = mktime(&taskDate);
  byDate.insert(std::make_pair(date, newEntityTask));
}

void TaskService::AddSubtask(const std::string& rootTaskName, const Task& subtask,const Task::Priority& priority){
  std::string rootTaskID = GetTaskIDByName(rootTaskName);

  std::string newID = rootTaskID + "s" + std::to_string(taskID.CreateID());
  auto newEntityTask = std::make_shared<TaskEntity>(std::make_shared<Task>(subtask), newID);
  tasks.insert(std::make_pair(newID, newEntityTask));
  byPriority.insert(std::make_pair(priority, newEntityTask));
  byName.insert(std::make_pair(subtask.GetName(), newEntityTask));
  byLabel.insert(std::make_pair(subtask.GetLabel(), newEntityTask));
  tm taskDate = subtask.GetDueDate();
  time_t date = mktime(&taskDate);
  byDate.insert(std::make_pair(date, newEntityTask));
}

void TaskService::RemoveTask(const std::string& taskName){
  std::string taskID = GetTaskIDByName(taskName);
  RemoveTaskFromByPriority(taskID); //weak_ptr to task
  RemoveTaskFromTasks(taskID);      //shared_ptr to task
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

std::vector<Task> TaskService::GetAllTasks(bool SortedByPrioriry){
  std::vector<Task> returnTasks;
  if (SortedByPrioriry){
    for (auto task : byPriority) {
      returnTasks.push_back(*task.second.lock()->GetTask());
    }
  } else {
    for (auto task : byDate){
      returnTasks.push_back(*task.second.lock()->GetTask());
    }
  }
  return returnTasks;
}

std::vector<Task> TaskService::GetAllTodayTasks(bool SortedByPrioriry){
  std::vector<Task> returnTasks;
  if (SortedByPrioriry){
    for (auto task : byPriority) {
      if (Date::IsToday(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(*task.second.lock()->GetTask());
      }
    }
  } else {
    for (auto task : byDate){
      if (Date::IsToday(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(*task.second.lock()->GetTask());
      }
    }
  }
  return returnTasks;
}

std::vector<Task> TaskService::GetAllWeekTasks(bool SortedByPrioriry){
  std::vector<Task> returnTasks;
  if (SortedByPrioriry){
    for (auto task : byPriority) {
      if (Date::IsThisWeek(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(*task.second.lock()->GetTask());
      }
    }
  } else {
    for (auto task : byDate){
      if (Date::IsThisWeek(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(*task.second.lock()->GetTask());
      }
    }
  }
  return returnTasks;
}

std::vector<Task> TaskService::GetAllTaskByLabel(std::string label, bool SortedByPrioriry){
  std::vector<Task> returnTasks;
  if (SortedByPrioriry){
    for (auto task : byPriority) {
      if (task.second.lock()->GetTaskLabel() == label){
        returnTasks.push_back(*task.second.lock()->GetTask());
      }
    }
  } else {
    for (auto task : byLabel){
      if (task.second.lock()->GetTaskLabel() == label){
        returnTasks.push_back(*task.second.lock()->GetTask());
      }
    }
  }
  return returnTasks;
}

std::vector<Task> TaskService::GetAllTaskByName(std::string name, bool SortedByPrioriry){
  std::vector<Task> returnTasks;
  if (SortedByPrioriry){
    for (auto task : byPriority) {
      if (task.second.lock()->GetTaskLabel() == name){
        returnTasks.push_back(*task.second.lock()->GetTask());
      }
    }
  } else {
    for (auto task : byName){
      if (task.second.lock()->GetTaskLabel() == name){
        returnTasks.push_back(*task.second.lock()->GetTask());
      }
    }
  }
  return returnTasks;
}