//
// Created by R2D2 on 15.07.2020.
//

#include "TaskService.h"
#include <string>
#include <vector>

TaskService::TaskService() : taskIDGenerate_(){}
TaskService::~TaskService() = default;

void TaskService::AddTask(const Task& task, const Task::Priority& priority){
  TaskID newTaskID = taskIDGenerate_.Generate();
  auto newEntityTask = std::make_shared<TaskEntity>(task, newTaskID);
  tasks_.insert(std::make_pair(newTaskID.GetID(), newEntityTask));
  taskView_.AddTask(newEntityTask);
}

bool TaskService::AddSubtask(const TaskID& rootTaskID, const Task& subtask,const Task::Priority& priority){
  if (tasks_.find(rootTaskID.GetID()) == tasks_.end()){
    return false;
  }
  TaskID newTaskID =  taskIDGenerate_.Generate();
  auto newEntityTask = std::make_shared<TaskEntity>(subtask, TaskID(newTaskID));
  tasks_[rootTaskID.GetID()]->AddSubtasks(newEntityTask);
  tasks_.insert(std::make_pair(newTaskID.GetID(), newEntityTask));
  taskView_.AddTask(newEntityTask);
  return true;
}

std::vector<TaskDTO> TaskService::GetTasks(const bool& byPriority){
  auto sortedTasks = taskView_.GetTasks();
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTodayTasks(const bool& byPriority){
  auto sortedTasks = taskView_.GetTodayTasks();
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetWeekTasks(const bool& byPriority){
  auto sortedTasks = taskView_.GetWeekTasks();
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTasksByLabel(const std::string& label, const bool& byPriority){
  auto sortedTasks = taskView_.GetTasksByLabel(label);
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTasksByName(const std::string& name, const bool& byPriority){
  auto sortedTasks = taskView_.GetTasksByName(name);
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTasksByPriority(Task::Priority priority){
  auto sortedTasks = taskView_.GetTasksByPriority(priority);
  return MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::MakeTasksDTObyPriority(const std::vector<TaskEntity>& tasksForDTO){
  std::multimap<Task::Priority, TaskEntity> sortedStore;
  for (auto task : tasksForDTO){
    sortedStore.insert(std::make_pair(task.GetTaskPriority(), task));
  }

  std::vector<TaskDTO> tasksDTO;
  for (auto task : sortedStore){
    tasksDTO.push_back(CreateDTO(task.second));
  }

  return tasksDTO;
}

std::vector<TaskDTO> TaskService::MakeTasksDTO(const std::vector<TaskEntity>& tasksForDTO){
  std::vector<TaskDTO> tasksDTO;
  for (auto task : tasksForDTO){
    tasksDTO.push_back(CreateDTO(task));
  }
  return tasksDTO;
}

TaskDTO TaskService::CreateDTO(const TaskEntity& task) {
  return TaskDTO(task.GetTask(), task.IsComplete(), task.GetId());
}