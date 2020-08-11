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

std::vector<TaskEntity> TaskView::GetTasks(){
  std::vector<TaskEntity> returnTasks;
    for (auto dates : byDate_){
      for (auto tasks : dates.second){
        returnTasks.push_back(*tasks.second.lock());
      }
    }
  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTodayTasks(){
  std::vector<TaskEntity> returnTasks;
  auto currentDay = Date::GetCurrentTime();
  auto tasksToday = byDate_.find(currentDay);

  if (tasksToday != byDate_.end()){
    for (auto task : byDate_[currentDay]){
      returnTasks.push_back(*task.second.lock());
    }
  }

  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetWeekTasks(){
  std::vector<TaskEntity> returnTasks;
  for (auto dates : byDate_){
    for (auto tasks : dates.second){
      if (Date::IsThisWeek(tasks.second.lock()->GetTaskDueDate().Get())){
        returnTasks.push_back(*tasks.second.lock());
      }
    }
  }
  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTasksByLabel(const std::string& label){
  std::vector<TaskEntity> returnTasks;
  auto tasksByLabel = byLabel_.find(label);

  if (tasksByLabel != byLabel_.end()){
    for (auto task : byLabel_[label]){
      returnTasks.push_back(*task.second.lock());
    }
  }

  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTasksByName(const std::string& name){
  std::vector<TaskEntity> returnTasks;
  auto tasksByName = byName_.find(name);

  if (tasksByName != byName_.end()){
    for (auto task : byName_[name]){
      returnTasks.push_back(*task.second.lock());
    }
  }
  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTasksByPriority(Priority taskPriority){
  std::vector<TaskEntity> returnTasks;
  auto tasksByPriority = byPriority_.find(taskPriority);
  if (tasksByPriority != byPriority_.end()){
    for (auto task : byPriority_[taskPriority]){
      returnTasks.push_back(*task.second.lock());
    }
  }
  return returnTasks;
}
