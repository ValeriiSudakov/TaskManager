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
  std::multimap<Priority, TaskEntity> sortedStore;
  for (const auto& task : tasksForDTO){
    sortedStore.insert(std::make_pair(task.GetPriority(), task));
  }

  std::vector<TaskDTO> tasksDTO;
  for (const auto& task : sortedStore){
    auto dto = TaskDTO::Create(task.second.GetName(), task.second.GetLabel(), task.second.GetPriority(),
                               task.second.GetDueDate(), task.second.IsComplete(), task.second.GetId());
    tasksDTO.push_back(dto);
  }

  return tasksDTO;
}