//
// Created by valeriisudakov on 06.10.20.
//

#ifndef TASKMANAGER_CORE_MEMORY_MODEL_REPOSITORIESFACTORY_TASKREPOSITORYFACTORY_H_
#define TASKMANAGER_CORE_MEMORY_MODEL_REPOSITORIESFACTORY_TASKREPOSITORYFACTORY_H_
#include "RepositoriesFactory.h"
#include "Repository/TaskRepositoryClass.h"

class TaskRepositoryFactory : public RepositoriesFactory {
 public:
  std::unique_ptr<TaskRepository> Create() override{
    auto storage = std::make_unique<TaskStorageClass>();
    auto view = std::make_unique<TaskViewClass>();
    return std::move(std::make_unique<TaskRepositoryClass>(std::move(view), std::move(storage)));
  }
};
#endif //TASKMANAGER_CORE_MEMORY_MODEL_REPOSITORIESFACTORY_TASKREPOSITORYFACTORY_H_
