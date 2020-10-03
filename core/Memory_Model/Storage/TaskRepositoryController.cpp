//
// Created by valeriisudakov on 03.10.20.
//

#include "TaskRepositoryController.h"

const std::unique_ptr<TaskRepository>& TaskRepositoryController::Get() const {
  return tasksRepository_;
}