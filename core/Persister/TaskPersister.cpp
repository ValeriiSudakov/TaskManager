//
// Created by valeriisudakov on 29.09.20.
//

#include "TaskPersister.h"
#include "TaskPersisterUtils.h"

bool TaskPersister::Load() {
  Serialized::Storage storage;
  //read from stream
  for (auto& task : storage.tasks()){
    auto taskDTO = PersisterUtils::DTOFromSerializedTask(task);
    auto addTaskResult = repository_.AddTask(taskDTO);
    if (!addTaskResult.success_){
      return false;
    }
    auto nonConstTask = task;
    PersisterUtils::AddSubtasksToRepository(nonConstTask, addTaskResult.id_.value(), repository_);
  }

}

bool TaskPersister::Save() {
  auto tasks = repository_.GetTasks();
  if (tasks.empty()){
    return true;
  }

  Serialized::Storage storage;
  for (auto& task : tasks){
    if (task.GetID() == task.GetRootID()){
      auto serializedTask = std::move(PersisterUtils::SerializedTaskFromDTO(task));

      auto* allocatedTask = storage.add_tasks();
      PersisterUtils::FillTask(*allocatedTask, *serializedTask);

      PersisterUtils::AddSubtasks(*serializedTask, task, repository_);
    }
  }

  // write to stream
}