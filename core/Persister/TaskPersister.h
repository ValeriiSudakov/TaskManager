//
// Created by valeriisudakov on 29.09.20.
//

#ifndef TASKMANAGER_CORE_PERSISTER_TASKPERSISTER_H_
#define TASKMANAGER_CORE_PERSISTER_TASKPERSISTER_H_

#include "Persister.h"
class TaskRepositoryDTO;

namespace DataPersister {
  class TaskPersister : public DataPersister::Persister {
   public:
    TaskPersister(const std::string& fileName, TaskRepository& repository)
    : repository_(repository), fileName_(fileName) {}

   public:
    bool                                Save() override;
    bool                                Load() override;

   private:
    TaskRepository&                     repository_;
    std::string                         fileName_;

  };


  std::unique_ptr<SerializedTaskEntity> MakeSerializeTask(const TaskRepositoryDTO& task,
                                                          std::map<TaskID, TaskID>& idMapping);
  TaskRepositoryDTO                     DTOFromSerializedTask(const SerializedTaskEntity& entity);
  void                                  AddSerializedTask(SerializedStorage& storage, std::unique_ptr<SerializedTaskEntity>& task);
  bool                                  FillNewTasksToRepository(SerializedStorage& serializedStorage,
                                                                 TaskRepository& repository);
}
#endif //TASKMANAGER_CORE_PERSISTER_TASKPERSISTER_H_
