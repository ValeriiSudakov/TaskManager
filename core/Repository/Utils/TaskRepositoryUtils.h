//
// Created by valeriisudakov on 19.10.20.
//

#ifndef TASKMANAGER_CORE_REPOSITORY_UTILS_TASKREPOSITORYUTILS_H_
#define TASKMANAGER_CORE_REPOSITORY_UTILS_TASKREPOSITORYUTILS_H_
#include "Repository/DTO/TaskRepositoryDTO.h"
#include "Repository/Task/TaskEntity.h"
#include "Repository/Task/ID/TaskIDGenerate.h"

namespace task_repository_utils {

  TaskRepositoryDTO                  DTOFromEntity(const TaskEntity& entity);
  void                               VectorFromEntitiesToDTO(const std::vector<TaskEntity>& entities,
                                                             std::vector<TaskRepositoryDTO>& dto);
  std::optional<TaskEntity>          NewEntityFromDTO(const TaskRepositoryDTO& dto, TaskIDGenerate& generator,
                                                      std::optional<TaskID> rootID);
  void                               SortByPriority(std::vector<TaskRepositoryDTO>& tasks);
};

#endif //TASKMANAGER_CORE_REPOSITORY_UTILS_TASKREPOSITORYUTILS_H_
