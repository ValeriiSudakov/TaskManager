//
// Created by valeriisudakov on 24.09.20.
//

#include "fstream"
#include "TaskPersister.h"
#include "SerializeModel.pb.h"
#include "Memory_Model/Storage/TaskRepositoryClass.h"



bool TaskPersister::Save(const std::string &fileName, TaskRepository &repository) {
  std::ofstream file(fileName);
  if (!file.is_open()) {
    return false;
  }

  auto tasksToSave = repository.GetTaskStorage()->GetTasks();
  //        oldID  newID
  std::map<TaskID, TaskID> idMapping;
  int i = 0;
  for (const auto &task : tasksToSave) {
    idMapping.insert(std::make_pair(task.first, TaskID(i++)));
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


bool TaskPersister::Load(const std::string &fileName, std::unique_ptr<TaskRepository>& repository) {
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




