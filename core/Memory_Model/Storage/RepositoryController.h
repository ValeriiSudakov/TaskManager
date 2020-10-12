//
// Created by valeriisudakov on 06.10.20.
//

#ifndef TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_REPOSITORYCONTROLLER_H_
#define TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_REPOSITORYCONTROLLER_H_
#include <memory>
#include "TaskRepository.h"

class RepositoryController {
 public:
  virtual ~RepositoryController() = default;

  virtual const std::unique_ptr<TaskRepository>&            Get() const = 0;
  virtual bool                                              Save(const std::string& filename) = 0;
  virtual bool                                              Load(const std::string& filename) = 0;
};

#endif //TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_REPOSITORYCONTROLLER_H_
