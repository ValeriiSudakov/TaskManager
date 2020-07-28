//
// Created by valerii.sudakov on 7/27/2020.
//

#include "TaskView.h"
#include "Date.h"

void TaskView::AddTask(const std::weak_ptr<TaskEntity>& task){
  byPriority.insert(std::make_pair(task.lock()->GetTaskPriority(), task));
  tm date = task.lock()->GetTaskDueDate();
  byDate.insert(std::make_pair(mktime(&date), task));
  byName.insert(std::make_pair(task.lock()->GetTaskName(), task));
  byLabel.insert(std::make_pair(task.lock()->GetTaskLabel(), task));
}

void TaskView::RemoveTask(const std::string& taskID) {

}


std::vector<Task> TaskView::GetTasks(bool SortedByPrioriry){
  std::vector<Task> returnTasks;
  if (SortedByPrioriry){
    for (auto task : byPriority) {
      returnTasks.push_back(task.second.lock()->GetTask());
    }
  } else {
    for (auto task : byDate){
      returnTasks.push_back(task.second.lock()->GetTask());
    }
  }
  return returnTasks;
}

std::vector<Task> TaskView::GetTodayTasks(bool SortedByPrioriry){
  std::vector<Task> returnTasks;
  if (SortedByPrioriry){
    for (auto task : byPriority) {
      if (Date::IsToday(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(task.second.lock()->GetTask());
      }
    }
  } else {
    for (auto task : byDate){
      if (Date::IsToday(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(task.second.lock()->GetTask());
      }
    }
  }
  return returnTasks;
}

std::vector<Task> TaskView::GetWeekTasks(bool SortedByPrioriry){
  std::vector<Task> returnTasks;
  if (SortedByPrioriry){
    for (auto task : byPriority) {
      if (Date::IsThisWeek(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(task.second.lock()->GetTask());
      }
    }
  } else {
    for (auto task : byDate){
      if (Date::IsThisWeek(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(task.second.lock()->GetTask());
      }
    }
  }
  return returnTasks;
}

std::vector<Task> TaskView::GetTasksByLabel(const std::string& label, bool SortedByPrioriry){
  std::vector<Task> returnTasks;
  if (SortedByPrioriry){
    for (auto task : byPriority) {
      if (task.second.lock()->GetTaskLabel() == label){
        returnTasks.push_back(task.second.lock()->GetTask());
      }
    }
  } else {
    for (auto task : byLabel){
      if (task.second.lock()->GetTaskLabel() == label){
        returnTasks.push_back(task.second.lock()->GetTask());
      }
    }
  }
  return returnTasks;
}

std::vector<Task> TaskView::GetTasksByName(const std::string& name, bool SortedByPrioriry){
  std::vector<Task> returnTasks;
  if (SortedByPrioriry){
    for (auto task : byPriority) {
      if (task.second.lock()->GetTaskLabel() == name){
        returnTasks.push_back(task.second.lock()->GetTask());
      }
    }
  } else {
    for (auto task : byName){
      if (task.second.lock()->GetTaskLabel() == name){
        returnTasks.push_back(task.second.lock()->GetTask());
      }
    }
  }
  return returnTasks;
}