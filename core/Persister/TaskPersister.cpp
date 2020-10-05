//
// Created by valeriisudakov on 29.09.20.
//

#include "TaskPersister.h"
#include "TaskPersisterUtils.h"

bool TaskPersister::Load() {
  Serialized::Storage storage;
  //read from stream
  storage.ParseFromIstream(&file_);

  for (auto& task : storage.tasks()){
    auto taskDTO = PersisterUtils::DTOFromSerializedTask(task);
    if (!taskDTO.has_value()){
      return false;
    }
    auto addTaskResult = repository_.AddTask(taskDTO.value());
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
      Serialized::Task* newTask = storage.add_tasks();
      PersisterUtils::SerializedTaskFromDTO(task, *newTask);
      PersisterUtils::AddSubtasks(*newTask, task, repository_);
    }
  }

  // write to stream
  return storage.SerializeToOstream(&file_);
}