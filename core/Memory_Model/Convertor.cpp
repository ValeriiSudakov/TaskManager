//
// Created by valeriisudakov on 17.08.20.
//

#include "Convertor.h"

std::vector<TaskServiceDTO> convertor::toTaskDTO::notSortedVector(const std::vector<TaskEntity>& tasksForDTO){
  std::vector<TaskServiceDTO> tasksDTO;
  for (const auto& task : tasksForDTO){
    auto dto = TaskServiceDTO::Create(task.GetName(), task.GetLabel(), task.GetPriority(), task.GetDueDate(),
                                              task.IsComplete(), task.GetId());
    tasksDTO.push_back(dto);
  }

  return tasksDTO;
}

std::vector<TaskServiceDTO>  convertor::toTaskDTO::sortedVectorByPriority(const std::vector<TaskEntity>& tasksForDTO){
  std::vector<TaskServiceDTO> tasksDTO;
  for (const auto& task : tasksForDTO){
    auto dto = TaskServiceDTO::Create(task.GetName(), task.GetLabel(), task.GetPriority(),
                                              task.GetDueDate(), task.IsComplete(), task.GetId());
    tasksDTO.push_back(dto);
  }
  std::sort(tasksDTO.begin(), tasksDTO.end(), [](const TaskServiceDTO& a, const TaskServiceDTO& b) { return a.GetPriority() < b.GetPriority(); });
  return tasksDTO;
}