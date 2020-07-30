//
// Created by valerii.sudakov on 7/27/2020.
//

#include "TaskView.h"
#include "Date.h"
#include "TaskDTO.h"

void TaskView::AddTask(const std::weak_ptr<TaskEntity>& task){
  byPriority.insert(std::make_pair(task.lock()->GetTaskPriority(), task));
  tm date = task.lock()->GetTaskDueDate();
  byDate.insert(std::make_pair(mktime(&date), task));
  byName.insert(std::make_pair(task.lock()->GetTaskName(), task));
  byLabel.insert(std::make_pair(task.lock()->GetTaskLabel(), task));
}

void TaskView::RemoveTask(const std::string& taskID) {

}


std::vector<TaskEntity> TaskView::GetTasks(){
  std::vector<TaskEntity> returnTasks;
    for (auto task : byDate){
      returnTasks.push_back(*task.second.lock());
    }
  }
  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTodayTasks(){
  std::vector<TaskEntity> returnTasks;

    for (auto task : byDate){
      if (Date::IsToday(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(*task.second.lock());
      }
    }
  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetWeekTasks(){
  std::vector<TaskEntity> returnTasks;
    for (auto task : byDate){
      if (Date::IsThisWeek(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(*task.second.lock());
      }
    }
  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTasksByLabel(const std::string& label){
  std::vector<TaskEntity> returnTasks;
    for (auto task : byLabel){
      if (task.first == label){
        returnTasks.push_back(*task.second.lock());
      }
    }
  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTasksByName(const std::string& name){
  std::vector<TaskEntity> returnTasks;
    for (auto task : byName){
      if(task.first == name){
         returnTasks.push_back(*task.second.lock());
      }
    }
  return returnTasks;
}

std::vector<TaskEntity> TaskView::GetTasksByPriority(Task::Priority taskPriority){
  std::vector<TaskEntity> returnTasks;
  for (auto task : byPriority){
    if (task.first == taskPriority){
      returnTasks.push_back(*task.second.lock());
    }
  }
  return returnTasks;
}