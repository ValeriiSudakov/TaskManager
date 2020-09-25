//
// Created by valeriisudakov on 25.09.20.
//

#ifndef TASKMANAGER_CORE_DATAPERSISTER_DATAPERSISTER_H_
#define TASKMANAGER_CORE_DATAPERSISTER_DATAPERSISTER_H_
#include "SerializeModel.pb.h"
#include <string>
#include <memory>

class TaskEntity;
class TaskID;
class TaskRepository;
enum class Priority;

namespace DataPersister{
  class Persister;

  SerializePriority                     PriorityToSerializedPriority(const Priority& priority);
  Priority                              SerializedPriorityToPriority(const SerializePriority& priority);
  std::unique_ptr<SerializedTaskEntity> MakeSerializeTask(const TaskEntity& task,
                                                          std::map<TaskID, TaskID>& idMapping);
  void                                  AddSerializedTask(SerializedStorage& storage, std::unique_ptr<SerializedTaskEntity>& task);

  bool                                  FillNewTasksToRepository(SerializedStorage& serializedStorage,
                                                                 TaskRepository& repository);

}

class DataPersister::Persister{
 public:
  virtual ~Persister() = default;

  virtual bool Save(const std::string& fileName, TaskRepository& repository) = 0;
  virtual bool Load(const std::string& fileName, std::unique_ptr<TaskRepository>& repository) = 0;
};

#endif //TASKMANAGER_CORE_DATAPERSISTER_DATAPERSISTER_H_
