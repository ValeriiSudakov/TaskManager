//
// Created by valerii.sudakov on 7/27/2020.
//

#include "TaskViewClass.h"
#include "Date.h"

TaskViewClass::TaskViewClass() = default;

void TaskViewClass::AddTask(const std::weak_ptr<TaskEntity>& task){
  TaskID id = task.lock()->GetId();
  byPriority_[task.lock()->GetPriority()].insert(std::make_pair(id, task));
  byDate_[task.lock()->GetDueDate().Get()].insert(std::make_pair(id, task));
  byName_[task.lock()->GetName()].insert(std::make_pair(id, task));
  byLabel_[task.lock()->GetLabel()].insert(std::make_pair(id, task));
}

template <typename CollectionType, typename FindValueType>
bool TaskViewClass::RemoveFromMap(CollectionType& collection, const TaskID& id, const FindValueType& findValue){
  auto tasks = collection.find(findValue);
  if (tasks != collection.end()){
    auto task = tasks->second.find(id);
    if (task != tasks->second.end()){
      tasks->second.erase(id);
      if (tasks->second.empty()){
        collection.erase(tasks);
      }
      return true;
    }
  }
  return false;
}

bool TaskViewClass::RemoveTask(const std::weak_ptr<TaskEntity>& task){
  if (task.lock() == nullptr){
    return false;
  }
  TaskID id = task.lock()->GetId();
  RemoveFromMap(byName_, id, task.lock()->GetName());
  RemoveFromMap(byLabel_, id, task.lock()->GetLabel());
  RemoveFromMap(byDate_, id, task.lock()->GetDueDate().Get());
  RemoveFromMap(byPriority_, id, task.lock()->GetPriority());
  return true;
}

std::vector<TaskEntity> TaskViewClass::GetTasks() const{
  std::vector<TaskEntity> returnTasks;
    for (const auto& dates : byDate_){
      for (const auto& tasks : dates.second){
        returnTasks.push_back(*tasks.second.lock());
      }
    }
  return returnTasks;
}

std::vector<TaskEntity> TaskViewClass::GetTodayTasks() const{
  std::vector<TaskEntity> returnTasks;
  auto currentDay = Date::GetCurrentTime();
  auto tasksToday = byDate_.find(currentDay);

  if (tasksToday != byDate_.end()){
    for (const auto& task : tasksToday->second){
      returnTasks.push_back(*task.second.lock());
    }
  }

  return returnTasks;
}

std::vector<TaskEntity> TaskViewClass::GetWeekTasks() const{
  std::vector<TaskEntity> returnTasks;

  std::cout<<"Begin of week: " << Date(boost::gregorian::date((int)Date::BeginOfWeek())).ToString() <<"\n";

  int weekBegins = Date::BeginOfWeek();
  int weekEnds = Date::EndOfWeek();
  int currentDay = weekBegins;

  while (currentDay <= weekEnds){
    auto taskWeek = byDate_.find(boost::gregorian::date(currentDay));
    if (taskWeek != byDate_.end()){
      for (const auto& tasks : taskWeek->second){
        returnTasks.push_back(*tasks.second.lock());
      }
    }
    currentDay++;
  }

  return returnTasks;
}

std::vector<TaskEntity> TaskViewClass::GetTasksByLabel(const std::string& label) const{
  std::vector<TaskEntity> returnTasks;
  auto tasksByLabel = byLabel_.find(label);

  if (tasksByLabel != byLabel_.end()){
    for (const auto& task : tasksByLabel->second){
      returnTasks.push_back(*task.second.lock());
    }
  }

  return returnTasks;
}

std::vector<TaskEntity> TaskViewClass::GetTasksByName(const std::string& name) const{
  std::vector<TaskEntity> returnTasks;
  auto tasksByName = byName_.find(name);

  if (tasksByName != byName_.end()){
    for (const auto& task : tasksByName->second){
      returnTasks.push_back(*task.second.lock());
    }
  }

  return returnTasks;
}

std::vector<TaskEntity> TaskViewClass::GetTasksByPriority(Priority taskPriority) const{
  std::vector<TaskEntity> returnTasks;
  auto tasksByPriority = byPriority_.find(taskPriority);

  if (tasksByPriority != byPriority_.end()){
    for (const auto& task : tasksByPriority->second){
      returnTasks.push_back(*task.second.lock());
    }
  }

  return returnTasks;
}
