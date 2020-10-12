//
// Created by valeriisudakov on 03.10.20.
//

#include "TaskRepositoryController.h"
#include "Persister/TaskPersister.h"
#include "Persister/TaskPersisterUtils.h"
#include <future>

const std::unique_ptr<TaskRepository>& TaskRepositoryController::Get() const {
  return tasksRepository_;
}

bool TaskRepositoryController::Save(const std::string& filename) {
  std::fstream file(filename, std::ios::out);
  auto persister = PersisterUtils::Create(*tasksRepository_, file);

  auto save = std::async(std::bind(&Persister::Save, persister.get()));
  save.wait();

  file.close();
  return save.get();
}

bool TaskRepositoryController::Load(const std::string& filename) {
  std::fstream file(filename, std::ios::in);
  auto newRepository = std::move(repositoryFactory_->Create());
  auto persister = PersisterUtils::Create(*newRepository, file);

  auto load = std::async(std::bind(&Persister::Load, persister.get()));
  load.wait();

  bool loadSuccess = load.get();
  if (loadSuccess){
    std::swap(tasksRepository_, newRepository);
  }
  file.close();
  return loadSuccess;
}