//
// Created by valeriisudakov on 01.10.20.
//

#include "TaskDtoUtils.h"

std::optional<TaskServiceDTO> TaskServiceUtils::MakeTaskDTO(const TaskRepositoryDTO& task) {
  auto newTask = TaskServiceDTO::Create(task.GetName(), task.GetLabel(), task.GetPriority(), task.GetDate(),
                                        task.Complete(), task.GetID());
  return newTask;
}

std::vector<TaskServiceDTO> TaskServiceUtils::MakeTasksDTO(const std::vector<TaskRepositoryDTO> &tasksForDTO) {
  std::vector<TaskServiceDTO> result;
  for (const auto& task : tasksForDTO){
    result.push_back(MakeTaskDTO(task).value());
  }
  return result;
}

TaskRepositoryDTO TaskServiceUtils::MakeTaskRepositoryDTO(const TaskServiceDTO &task) {
  auto newTask =  TaskRepositoryDTO::Create(task.GetName(), task.GetLabel(), task.GetPriority(), task.GetDate());
  return newTask.value();
}