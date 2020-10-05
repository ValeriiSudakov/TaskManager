//
// Created by valeriisudakov on 03.10.20.
//

#ifndef TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_TASKREPOSITORYCONTOLLER_H_
#define TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_TASKREPOSITORYCONTOLLER_H_
#include "TaskRepository.h"

class TaskRepositoryController {
 public:
  TaskRepositoryController(const std::function<std::unique_ptr<TaskRepository>()>& repositoryFactory)
    : repositoryFactory_(repositoryFactory) {
      tasksRepository_ = std::move(repositoryFactory_());
  }

 public:
  const std::unique_ptr<TaskRepository>&            Get() const;
  bool                                              Save();
  bool                                              Load();
 private:
  std::unique_ptr<TaskRepository>                   tasksRepository_;
  std::function<std::unique_ptr<TaskRepository>()>  repositoryFactory_;
};

#endif //TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_TASKREPOSITORYCONTOLLER_H_
