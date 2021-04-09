//
// Created by valeriisudakov on 29.09.20.
//

#include "TaskPersister.h"
#include "TaskPersisterUtils.h"

bool TaskPersister::Load() {
  proto::Storage storage;
  //read from stream
  storage.ParseFromIstream(&file_);

  for (auto& task : storage.tasks()){
    auto taskDTO = persister_utils::DTOFromSerializedTask(task);
    if (!taskDTO.has_value()){
      return false;
    }
    auto addTaskResult = repository_.AddTask(taskDTO.value());
    if (!addTaskResult.success_){
      return false;
    }
    auto nonConstTask = task;
    persister_utils::AddSubtasksToRepository(nonConstTask, addTaskResult.id_.value(), repository_);
  }
  return true;
}

bool TaskPersister::Save() {
  auto tasks = repository_.GetTasks();
  if (tasks.empty()){
    return true;
  }

  proto::Storage storage;
  for (auto& task : tasks){
    if (task.GetID() == task.GetRootID()){
      proto::Task* newTask = storage.add_tasks();
      persister_utils::SerializedTaskFromDTO(task, *newTask);
      persister_utils::AddSubtasks(*newTask, task, repository_);
    }
  }

  // write to stream
  return storage.SerializeToOstream(&file_);
}