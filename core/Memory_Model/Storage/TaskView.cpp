//
// Created by valerii.sudakov on 7/27/2020.
//

#include "TaskView.h"
#include "Date/Date.h"

TaskView::TaskView() = default;

void TaskView::AddTask(const std::weak_ptr<TaskEntity>& task){
  TaskID id = task.lock()->GetId();
  byPriority_[task.lock()->GetPriority()].insert(std::make_pair(id, task));
  byDate_[task.lock()->GetDueDate().Get()].insert(std::make_pair(id, task));
  byName_[task.lock()->GetName()].insert(std::make_pair(id, task));
  byLabel_[task.lock()->GetLabel()].insert(std::make_pair(id, task));
}

template <typename CollectionType, typename FindValueType>
bool TaskView::RemoveFromMap(CollectionType& collection,const TaskID& id, const FindValueType& findValue){
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

bool TaskView::RemoveTask(const std::weak_ptr<TaskEntity>& task){
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

std::vector<TaskEntity> TaskView::GetTasks() const{
  std::vector<TaskEntity> returnTasks;
    for (const auto& dates : byDate_){
      for (const auto& tasks : dates.second){
        returnTasks.push_back(*tasks.second.lock());
      }
    }
  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTodayTasks() const{
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

std::vector<TaskEntity> TaskView::GetWeekTasks() const{
  std::vector<TaskEntity> returnTasks;
  int dayOfEndOfWeek = Date::DayForEndOfWeek();
  int currentDay = Date::GetCurrentTime().day_number();
  auto taskWeek = byDate_.find(boost::gregorian::date(currentDay));

  while (currentDay <= dayOfEndOfWeek && taskWeek != byDate_.end()){
    for (const auto& tasks : taskWeek->second){
      returnTasks.push_back(*tasks.second.lock());
    }
    currentDay++;
    taskWeek = byDate_.find(boost::gregorian::date(currentDay));
  }

  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTasksByLabel(const std::string& label) const{
  std::vector<TaskEntity> returnTasks;
  auto tasksByLabel = byLabel_.find(label);

  if (tasksByLabel != byLabel_.end()){
    for (const auto& task : tasksByLabel->second){
      returnTasks.push_back(*task.second.lock());
    }
  }

  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTasksByName(const std::string& name) const{
  std::vector<TaskEntity> returnTasks;
  auto tasksByName = byName_.find(name);

  if (tasksByName != byName_.end()){
    for (const auto& task : tasksByName->second){
      returnTasks.push_back(*task.second.lock());
    }
  }

  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTasksByPriority(Priority taskPriority) const{
  std::vector<TaskEntity> returnTasks;
  auto tasksByPriority = byPriority_.find(taskPriority);

  if (tasksByPriority != byPriority_.end()){
    for (const auto& task : tasksByPriority->second){
      returnTasks.push_back(*task.second.lock());
    }
  }

  return returnTasks;
}
