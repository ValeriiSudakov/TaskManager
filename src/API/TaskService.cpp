//
// Created by R2D2 on 15.07.2020.
//

#include "TaskService.h"
#include <string>
#include <vector>


AddTaskResult TaskService::AddTask(const TaskDTO& task, const Priority& priority){
  AddTaskResult addNewTask = tasksRepository_.AddTask(task, priority);
  return addNewTask.success_;
}

AddTaskResult TaskService::AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask,const Priority& priority){
  auto addNewSubtask = tasksRepository_.AddSubtask(rootTaskID, subtask, priority);
  return addNewSubtask.success_;
}

bool TaskService::RemoveTask(const TaskID& ID){
  auto result = tasksRepository_.RemoveTask(ID);
  return result;
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

std::vector<TaskDTO> TaskService::GetTasksByPriority(const Priority& priority){
  auto sortedTasks = tasksRepository_.GetTaskView().GetTasksByPriority(priority);
  return MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::MakeTasksDTObyPriority(const std::vector<TaskEntity>& tasksForDTO){
  std::multimap<Priority, TaskEntity> sortedStore;
  for (auto task : tasksForDTO){
    sortedStore.insert(std::make_pair(task.GetTaskPriority(), task));
  }

  std::vector<TaskDTO> tasksDTO;
  for (auto task : sortedStore){
    auto dto = TaskDTO::CreateFromTaskEntity(task.second);
    tasksDTO.push_back(dto);
  }

  return tasksDTO;
}

std::vector<TaskDTO> TaskService::MakeTasksDTO(const std::vector<TaskEntity>& tasksForDTO){
  std::vector<TaskDTO> tasksDTO;
  for (auto task : tasksForDTO){
    auto dto = TaskDTO::CreateFromTaskEntity(task);
    tasksDTO.push_back(dto);
  }
  return tasksDTO;
}
