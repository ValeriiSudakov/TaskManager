//
// Created by R2D2 on 15.07.2020.
//

#include "TaskService.h"
#include <string>
#include <vector>


AddTaskResult TaskService::AddTask(const TaskDTO& task){
  AddTaskResult addNewTask = tasksRepository_.AddTask(task);
  return addNewTask.success_;
}

AddTaskResult TaskService::AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask){
  auto addNewSubtask = tasksRepository_.AddSubtask(rootTaskID, subtask);
  return addNewSubtask.success_;
}

bool TaskService::RemoveTask(const TaskID& ID){
  auto result = tasksRepository_.RemoveTask(ID);
  return result;
}

std::optional<TaskDTO> TaskService::GetTask(const TaskID& id) const{
  auto task = tasksRepository_.GetTaskStorage().GetTask(id.Get());
  return task.has_value() ? std::make_optional(TaskDTO::CreateFromTaskEntity(*task.value())) : std::nullopt;
}

std::vector<TaskDTO> TaskService::GetTasks(bool byPriority) const{
  auto sortedTasks = tasksRepository_.GetTaskView().GetTasks();
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTodayTasks(bool byPriority) const{
  auto sortedTasks = tasksRepository_.GetTaskView().GetTodayTasks();
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetWeekTasks(bool byPriority) const{
  auto sortedTasks = tasksRepository_.GetTaskView().GetWeekTasks();
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTasksByLabel(const std::string& label, bool byPriority) const{
  auto sortedTasks = tasksRepository_.GetTaskView().GetTasksByLabel(label);
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTasksByName(const std::string& name, bool byPriority) const{
  auto sortedTasks = tasksRepository_.GetTaskView().GetTasksByName(name);
  return byPriority ? MakeTasksDTObyPriority(sortedTasks) : MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTasksByPriority(const Priority& priority) const{
  auto sortedTasks = tasksRepository_.GetTaskView().GetTasksByPriority(priority);
  return MakeTasksDTO(sortedTasks);
}

std::vector<TaskDTO> TaskService::MakeTasksDTObyPriority(const std::vector<TaskEntity>& tasksForDTO) const{
  std::multimap<Priority, TaskEntity> sortedStore;
  for (const auto& task : tasksForDTO){
    sortedStore.insert(std::make_pair(task.GetPriority(), task));
  }

  std::vector<TaskDTO> tasksDTO;
  for (const auto& task : sortedStore){
    auto dto = TaskDTO::CreateFromTaskEntity(task.second);
    tasksDTO.push_back(dto);
  }

  return tasksDTO;
}

std::vector<TaskDTO> TaskService::MakeTasksDTO(const std::vector<TaskEntity>& tasksForDTO) const{
  std::vector<TaskDTO> tasksDTO;
  for (const auto& task : tasksForDTO){
    auto dto = TaskDTO::CreateFromTaskEntity(task);
    tasksDTO.push_back(dto);
  }

  return tasksDTO;
}
