//
// Created by valeriisudakov on 03.10.20.
//

#include "TaskRepositoryController.h"
#include "Persister/TaskPersister.h"
#include "Persister/TaskPersisterUtils.h"

const std::unique_ptr<TaskRepository>& TaskRepositoryController::Get() const {
  return tasksRepository_;
}

bool TaskRepositoryController::Save() {
  std::fstream file("Tasks.txt", std::ios::out);
  auto persister = PersisterUtils::Create(*tasksRepository_, file);
  auto result = persister->Save();
  file.close();
  return result;
}

bool TaskRepositoryController::Load() {
  std::fstream file("Tasks.txt", std::ios::in);
  auto newRepository = std::move(repositoryFactory_->Create());
  auto persister = PersisterUtils::Create(*newRepository, file);
  auto result = persister->Load();

  if (result){
    std::swap(tasksRepository_, newRepository);
  }
  file.close();
  return result;
}