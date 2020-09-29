//
// Created by valeriisudakov on 29.09.20.
//

#include "assert.h"
#include "TaskPersister.h"
#include "fstream"
#include "SerializedModel.pb.h"
#include "Memory_Model/Storage/TaskRepositoryClass.h"


bool DataPersister::TaskPersister::Save() {
  std::ofstream file(fileName_);
  if (!file.is_open()) {
    return false;
  }

  auto tasksToSave = repository_.GetTasks();
  //        oldID  newID
  std::map<TaskID, TaskID> idMapping;
  TaskIDGenerate newID;
  for (const auto &task : tasksToSave) {
    idMapping.insert(std::make_pair(task.GetID(), newID.Generate()));
  }

  SerializedStorage storageToSave;

  for (const auto &task : tasksToSave) {
    auto newTask = DataPersister::MakeSerializeTask(task, idMapping);
    DataPersister::AddSerializedTask(storageToSave, newTask);
  }

  storageToSave.SerializeToOstream(&file);
  file.close();
  return true;
}


bool DataPersister::TaskPersister::Load() {
  std::ifstream file(fileName_);
  if (!file.is_open()) {
    return false;
  }

  SerializedStorage storageToLoad;
  storageToLoad.ParseFromIstream(&file);
  file.close();

  std::unique_ptr<TaskRepository> newRepository = std::make_unique<TaskRepositoryClass>(std::make_unique<TaskViewClass>(),
                                                                                        std::make_unique<TaskStorageClass>());
  auto result = DataPersister::FillNewTasksToRepository(storageToLoad, *newRepository);
  if (!result){
    return false;
  }
  repository_.ResetRepository();
  for (const auto& task : newRepository->GetTasks()){
    task.GetRootID() == task.GetID() ? repository_.AddTask(task) : repository_.AddSubtask(task.GetRootID(), task);
  }

  return true;
}


void DataPersister::AddSerializedTask(SerializedStorage& storage, std::unique_ptr<SerializedTaskEntity>& task){
  auto* addTask = storage.add_tasks();
  addTask->set_allocated_task (task->release_task());
  addTask->set_id             (task->id());
  addTask->set_rootid         (task->rootid());
  addTask->set_complete       (task->complete());
}

std::unique_ptr<SerializedTaskEntity> DataPersister::MakeSerializeTask(const TaskRepositoryDTO& task,
                                                                       std::map<TaskID, TaskID>& idMapping){
  auto newTask = std::make_unique<SerializedTask>();
  newTask->set_name     (task.GetName());
  newTask->set_label    (task.GetLabel());
  newTask->set_priority (PriorityToSerializedPriority(task.GetPriority()));
  newTask->set_date     (task.GetDate().Get().day_number());

  auto newTaskEntity = std::make_unique<SerializedTaskEntity>();
  newTaskEntity->set_allocated_task(newTask.release());

  auto newID = idMapping[task.GetID()];
  newTaskEntity->set_id(newID.Get());

  auto newParentID = idMapping[task.GetRootID()];
  newTaskEntity->set_rootid(newParentID.Get());

  newTaskEntity->set_complete(task.Complete());

  return std::move(newTaskEntity);
}

bool DataPersister::FillNewTasksToRepository(SerializedStorage& serializedStorage,
                                             TaskRepository& repository){
  for (const auto& task : serializedStorage.tasks()){
    auto newTask = Task::Create(task.task().name(), task.task().label(),
                                SerializedPriorityToPriority(task.task().priority()),
                                boost::gregorian::date(task.task().date()));
    if (!newTask.has_value()){
      return false;
    }
    if (task.has_rootid()) {
      repository.AddTask(DTOFromSerializedTask(task));
    } else{
      repository.AddSubtask(TaskID(task.rootid()), DTOFromSerializedTask(task));
    }
    if (task.complete()){
      auto result = repository.SetTaskComplete(TaskID(task.id()));
      if (!result){
        return false;
      }
    }
  }
  return true;
}

TaskRepositoryDTO DataPersister::DTOFromSerializedTask(const SerializedTaskEntity& entity){
  auto dto = TaskRepositoryDTO::Create(entity.task().name(), entity.task().label(),
                                       SerializedPriorityToPriority(entity.task().priority()),
                                       Date(boost::gregorian::date(entity.task().date())),
                                       entity.complete(), entity.id(), TaskID(entity.rootid()));
  assert(dto.has_value());
  return dto.value();
}