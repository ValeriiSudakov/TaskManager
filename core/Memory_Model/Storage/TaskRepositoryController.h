//
// Created by valeriisudakov on 03.10.20.
//

#ifndef TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_TASKREPOSITORYCONTOLLER_H_
#define TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_TASKREPOSITORYCONTOLLER_H_
#include "TaskRepository.h"
#include "Memory_Model/RepositoriesFactory/RepositoriesFactory.h"

class TaskRepositoryController {
 public:
  TaskRepositoryController(std::unique_ptr<RepositoriesFactory> repositoryFactory)
    : repositoryFactory_(std::move(repositoryFactory)) {
    tasksRepository_ = std::move(repositoryFactory_->Create());
  }

 public:
  const std::unique_ptr<TaskRepository>&            Get() const;
  bool                                              Save();
  bool                                              Load();
 private:
  std::unique_ptr<TaskRepository>                   tasksRepository_;
  std::unique_ptr<RepositoriesFactory>              repositoryFactory_;
};

#endif //TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_TASKREPOSITORYCONTOLLER_H_
