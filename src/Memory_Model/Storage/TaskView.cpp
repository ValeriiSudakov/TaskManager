//
// Created by valerii.sudakov on 7/27/2020.
//

#include "TaskView.h"
#include "Memory_Model/Date/Date.h"

void TaskView::AddTask(const std::weak_ptr<TaskEntity>& task){
  TaskID id = task.lock()->GetId();
  byPriority_[task.lock()->GetTaskPriority()].insert(std::make_pair(id.GetID(), task));
  byDate_[task.lock()->GetTaskDueDate().Get()].insert(std::make_pair(id.GetID(), task));
  byName_[task.lock()->GetTaskName()].insert(std::make_pair(id.GetID(), task));
  byLabel_[task.lock()->GetTaskLabel()].insert(std::make_pair(id.GetID(), task));
}


bool TaskView::RemoveTask(const std::weak_ptr<TaskEntity>& task){
  TaskID id = task.lock()->GetId();
  auto byPriority = byPriority_.find(task.lock()->GetTaskPriority());
  if (byPriority == byPriority_.end()){
    return false;
  }
  byPriority->second.erase(id.GetID());

  auto byDate = byDate_.find(task.lock()->GetTaskDueDate().Get());
  if (byDate == byDate_.end()){
    return false;
  }
  byDate->second.erase(id.GetID());

  auto byName = byName_.find(task.lock()->GetTaskName());
  if (byName == byName_.end()){
    return false;
  }
  byName->second.erase(id.GetID());

  auto byLabel = byLabel_.find(task.lock()->GetTaskLabel());
  if (byLabel == byLabel_.end()){
    return false;
  }
  byLabel->second.erase(id.GetID());
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

  if (taskWeek != byDate_.end()){
    while (currentDay <= dayOfEndOfWeek){
      for (const auto& tasks : taskWeek->second){
        returnTasks.push_back(*tasks.second.lock());
      }
      currentDay++;
    }
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
