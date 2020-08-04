//
// Created by R2D2 on 15.07.2020.
//

#include "TaskService.h"
#include <string>
#include <vector>


void TaskService::AddTask(const TaskDTO& task, const Task::Priority& priority){
  auto newTask = tasksRepository_.GetTaskStorage().AddTask(task.GetTask(), priority);
  tasksRepository_.GetTaskView().AddTask(newTask);
}

bool TaskService::AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask,const Task::Priority& priority){
  auto newSubtask = tasksRepository_.GetTaskStorage().AddSubtask(rootTaskID, subtask.GetTask(), priority);
  if (newSubtask.has_value()){
    tasksRepository_.GetTaskView().AddTask(newSubtask.value());
    return true;
  }
  return false;
}

std::vector<TaskDTO> TaskService::GetTasks(const bool& byPriority){
  auto sortedTasks = tasksRepository_.GetTaskView().GetTasks();
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTodayTasks(const bool& byPriority){
  auto sortedTasks = tasksRepository_.GetTaskView().GetTodayTasks();
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetWeekTasks(const bool& byPriority){
  auto sortedTasks = tasksRepository_.GetTaskView().GetWeekTasks();
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTasksByLabel(const std::string& label, const bool& byPriority){
  auto sortedTasks = tasksRepository_.GetTaskView().GetTasksByLabel(label);
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTasksByName(const std::string& name, const bool& byPriority){
  auto sortedTasks = tasksRepository_.GetTaskView().GetTasksByName(name);
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTasksByPriority(const Task::Priority& priority){
  auto sortedTasks = tasksRepository_.GetTaskView().GetTasksByPriority(priority);
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