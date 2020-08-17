//
// Created by valeriisudakov on 17.08.20.
//

#include "Convertor.h"

std::vector<TaskDTO> convertor::toTaskDTO::notSortedVector(const std::vector<TaskEntity>& tasksForDTO){
  std::vector<TaskDTO> tasksDTO;
  for (const auto& task : tasksForDTO){
    auto dto = TaskDTO::Create(task.GetName(), task.GetLabel(), task.GetPriority(), task.GetDueDate(),
                               task.IsComplete(), task.GetId());
    tasksDTO.push_back(dto);
  }

  return tasksDTO;
}

std::vector<TaskDTO>  convertor::toTaskDTO::sortedVectorByPriority(const std::vector<TaskEntity>& tasksForDTO){
  std::vector<TaskDTO> tasksDTO;
  for (const auto& task : tasksForDTO){
    auto dto = TaskDTO::Create(task.GetName(), task.GetLabel(), task.GetPriority(),
                               task.GetDueDate(), task.IsComplete(), task.GetId());
    tasksDTO.push_back(dto);
  }
  std::sort(tasksDTO.begin(), tasksDTO.end(), [](TaskDTO a, TaskDTO b) { return a.GetPriority() < b.GetPriority(); });
  return tasksDTO;
}