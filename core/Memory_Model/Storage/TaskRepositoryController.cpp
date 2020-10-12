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

bool TaskRepositoryController::Save() {
  std::fstream file("Tasks.txt", std::ios::out);
  auto persister = PersisterUtils::Create(*tasksRepository_, file);
  //auto result = persister->Save();
  auto thread = std::async(std::bind(&Persister::Save, persister.get()));
  thread.wait();
  auto result = thread.get();
  file.close();
  return result;
}

bool TaskRepositoryController::Load() {
  std::fstream file("Tasks.txt", std::ios::in);
  auto newRepository = std::move(repositoryFactory_->Create());
  auto persister = PersisterUtils::Create(*newRepository, file);
  //auto result = persister->Load();
  auto thread = std::async(std::bind(&Persister::Load, persister.get()));
  thread.wait();
  auto result = thread.get();
  if (result){
    std::swap(tasksRepository_, newRepository);
  }
  file.close();
  return result;
}