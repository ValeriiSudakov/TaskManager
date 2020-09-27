//
// Created by valeriisudakov on 24.09.20.
//

#include "fstream"
#include "TaskPersister.h"
#include "SerializeModel.pb.h"
#include "Memory_Model/Storage/TaskRepositoryClass.h"


bool DataPersister::TaskPersister::Save(const std::string &fileName, TaskRepository &repository) {
  std::ofstream file(fileName);
  if (!file.is_open()) {
    return false;
  }

  auto tasksToSave = repository.GetTaskStorage()->GetTasks();
  //        oldID  newID
  std::map<TaskID, TaskID> idMapping;
  TaskIDGenerate newID;
  for (const auto &task : tasksToSave) {
    idMapping.insert(std::make_pair(task.first, newID.Generate()));
  }

  SerializedStorage storageToSave;

  for (const auto &task : tasksToSave) {
    auto newTask = DataPersister::MakeSerializeTask(*task.second, idMapping);
    DataPersister::AddSerializedTask(storageToSave, newTask);
  }

  storageToSave.SerializeToOstream(&file);
  file.close();
  return true;
}


bool DataPersister::TaskPersister::Load(const std::string &fileName, std::unique_ptr<TaskRepository>& repository) {
  std::ifstream file(fileName);
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
  repository.reset();
  repository = std::move(newRepository);
  return true;
}


void DataPersister::AddSerializedTask(SerializedStorage& storage, std::unique_ptr<SerializedTaskEntity>& task){
  auto* addTask = storage.add_tasks();
  addTask->set_allocated_task (task->release_task());
  addTask->set_id             (task->id());
  addTask->set_rootid         (task->rootid());
  addTask->set_complete       (task->complete());
}

std::unique_ptr<SerializedTaskEntity> DataPersister::MakeSerializeTask(const TaskEntity& task,
                                                                       std::map<TaskID, TaskID>& idMapping){
  auto newTask = std::make_unique<SerializedTask>();
  newTask->set_name     (task.GetName());
  newTask->set_label    (task.GetLabel());
  newTask->set_priority (PriorityToSerializedPriority(task.GetPriority()));
  newTask->set_date     (task.GetDueDate().Get().day_number());

  auto newTaskEntity = std::make_unique<SerializedTaskEntity>();
  newTaskEntity->set_allocated_task(newTask.release());

  auto newID = idMapping[task.GetId()];
  newTaskEntity->set_id(newID.Get());

  auto newParentID = idMapping[task.GetParentId()];
  newTaskEntity->set_rootid(newParentID.Get());

  newTaskEntity->set_complete(task.IsComplete());

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
    if (task.rootid() == task.id()){
      repository.AddTask(newTask.value());
    } else{
      repository.AddSubtask(TaskID(task.rootid()), newTask.value());
    }
    if (task.complete()){
      auto toComplete = repository.GetTaskStorage()->GetTask(TaskID(task.id()));
      toComplete.value()->SetComplete();
    }
  }
  return true;
}


