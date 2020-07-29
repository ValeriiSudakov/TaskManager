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


std::vector<TaskDTO> TaskView::GetTasks(bool SortedByPriority){
  std::vector<TaskDTO> returnTasks;
  if (SortedByPriority){
    for (auto task : byPriority) {
      returnTasks.push_back(TaskDTO(task.second.lock()->GetTask(),
                                    task.second.lock()->IsComplete(),
                                    task.second.lock()->GetId()));
    }
  } else {
    for (auto task : byDate){
      returnTasks.push_back(TaskDTO(task.second.lock()->GetTask(),
                                    task.second.lock()->IsComplete(),
                                    task.second.lock()->GetId()));
    }
  }
  return returnTasks;
}

std::vector<TaskDTO> TaskView::GetTodayTasks(bool SortedByPriority){
  std::vector<TaskDTO> returnTasks;
  if (SortedByPriority){
    for (auto task : byPriority) {
      if (Date::IsToday(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(TaskDTO(task.second.lock()->GetTask(),
                                      task.second.lock()->IsComplete(),
                                      task.second.lock()->GetId()));
      }
    }
  } else {
    for (auto task : byDate){
      if (Date::IsToday(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(TaskDTO(task.second.lock()->GetTask(),
                                      task.second.lock()->IsComplete(),
                                      task.second.lock()->GetId()));
      }
    }
  }
  return returnTasks;
}

std::vector<TaskDTO> TaskView::GetWeekTasks(bool SortedByPriority){
  std::vector<TaskDTO> returnTasks;
  if (SortedByPriority){
    for (auto task : byPriority) {
      if (Date::IsThisWeek(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(TaskDTO(task.second.lock()->GetTask(),
                                      task.second.lock()->IsComplete(),
                                      task.second.lock()->GetId()));
      }
    }
  } else {
    for (auto task : byDate){
      if (Date::IsThisWeek(task.second.lock()->GetTaskDueDate())){
        returnTasks.push_back(TaskDTO(task.second.lock()->GetTask(),
                                      task.second.lock()->IsComplete(),
                                      task.second.lock()->GetId()));
      }
    }
  }
  return returnTasks;
}

std::vector<TaskDTO> TaskView::GetTasksByLabel(const std::string& label, bool SortedByPriority){
  std::vector<TaskDTO> returnTasks;
  if (SortedByPriority){
    for (auto task : byPriority) {
      if (task.second.lock()->GetTaskLabel() == label){
         returnTasks.push_back(TaskDTO(task.second.lock()->GetTask(),
                                       task.second.lock()->IsComplete(),
                                       task.second.lock()->GetId()));
      }
    }
  } else {
    for (auto task : byLabel){
      if (task.second.lock()->GetTaskLabel() == label){
        returnTasks.push_back(TaskDTO(task.second.lock()->GetTask(),
                                      task.second.lock()->IsComplete(),
                                      task.second.lock()->GetId()));
      }
    }
  }
  return returnTasks;
}

std::vector<TaskDTO> TaskView::GetTasksByName(const std::string& name, bool SortedByPriority){
  std::vector<TaskDTO> returnTasks;
  if (SortedByPriority){
    for (auto task : byPriority) {
      if (task.second.lock()->GetTaskName() == name){
        returnTasks.push_back(TaskDTO(task.second.lock()->GetTask(),
                                      task.second.lock()->IsComplete(),
                                      task.second.lock()->GetId()));
      }
    }
  } else {
    for (auto task : byName){
      if (task.second.lock()->GetTaskName() == name){
        returnTasks.push_back(TaskDTO(task.second.lock()->GetTask(),
                                      task.second.lock()->IsComplete(),
                                      task.second.lock()->GetId()));
      }
    }
  }
  return returnTasks;
}

std::vector<TaskDTO> TaskView::GetTasksByPriority(Task::Priority taskPriority){
  std::vector<TaskDTO> returnTasks;
  for (auto task : byPriority){
    if (task.first == taskPriority){
      returnTasks.push_back(TaskDTO(task.second.lock()->GetTask(),
                                    task.second.lock()->IsComplete(),
                                    task.second.lock()->GetId()));
    }
  }
  return returnTasks;
}