//
// Created by valerii.sudakov on 7/27/2020.
//

#include "TaskView.h"
#include "Memory Model/Date.h"

void TaskView::AddTask(const std::weak_ptr<TaskEntity>& task){
  byPriority_.insert(std::make_pair(task.lock()->GetTaskPriority(), task));

  tm date = task.lock()->GetTaskDueDate();
  byDate_.insert(std::make_pair(mktime(&date), task));

  byName_.insert(std::make_pair(task.lock()->GetTaskName(), task));
  byLabel_.insert(std::make_pair(task.lock()->GetTaskLabel(), task));
}

std::vector<TaskEntity> TaskView::GetTasks(){
  std::vector<TaskEntity> returnTasks;
    for (auto task : byDate_){
      returnTasks.push_back(*task.second.lock());
    }
  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTodayTasks(){
  std::vector<TaskEntity> returnTasks;
    for (auto task : byDate_){
      if (Date::IsToday(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(*task.second.lock());
      }
    }
  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetWeekTasks(){
  std::vector<TaskEntity> returnTasks;
    for (auto task : byDate_){
      if (Date::IsThisWeek(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(*task.second.lock());
      }
    }
  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTasksByLabel(const std::string& label){
  std::vector<TaskEntity> returnTasks;
  auto i = byLabel_.find(label); // find pos of label in map
  while(i != byLabel_.end()){
    returnTasks.push_back(*i->second.lock());
    if (i++->first != label) break;
  }
  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTasksByName(const std::string& name){
  std::vector<TaskEntity> returnTasks;
  auto i = byName_.find(name); // find pos of name in map
  while(i != byName_.end()){
    returnTasks.push_back(*i->second.lock());
    if (i++->first != name) break;
  }
  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTasksByPriority(Task::Priority taskPriority){
  std::vector<TaskEntity> returnTasks;
  auto i = byPriority_.find(taskPriority); // find pos of priority in map
  while(i != byPriority_.end()){
    returnTasks.push_back(*i->second.lock());
    if (i++->first != taskPriority) break;
  }
  return returnTasks;
}
