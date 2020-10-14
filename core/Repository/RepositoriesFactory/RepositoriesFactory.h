//
// Created by valeriisudakov on 06.10.20.
//

#ifndef TASKMANAGER_CORE_MEMORY_MODEL_REPOSITORIESFACTORY_REPOSITORIESFACTORY_H_
#define TASKMANAGER_CORE_MEMORY_MODEL_REPOSITORIESFACTORY_REPOSITORIESFACTORY_H_
#include "Repository/TaskRepository.h"

class RepositoriesFactory{
 public:
  virtual ~RepositoriesFactory() = default;

  virtual std::unique_ptr<TaskRepository> Create() = 0;
};

#endif //TASKMANAGER_CORE_MEMORY_MODEL_REPOSITORIESFACTORY_REPOSITORIESFACTORY_H_
