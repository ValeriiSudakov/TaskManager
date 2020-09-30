//
// Created by valeriisudakov on 30.09.20.
//

#ifndef TASKMANAGER_CORE_PERSISTER_TASKPERSISTERUTILS_H_
#define TASKMANAGER_CORE_PERSISTER_TASKPERSISTERUTILS_H_
#include "Memory_Model/Storage/TaskRepository.h"
#include "SerializedModel.pb.h"

namespace PersisterUtils{
  Priority                              SerializedPriorityToPriority(const Serialized::Priority& priority);
  Serialized::Priority                  PriorityToSerializedPriority(const Priority& priority);

  std::unique_ptr<Serialized::Task>     SerializedTaskFromDTO(const TaskRepositoryDTO& taskDTO);

  void                                  FillTask(Serialized::Task& newTask, Serialized::Task& data);

  void                                  AddSubtasks(Serialized::Task& serializedTask, TaskRepositoryDTO& task,
                                                    TaskRepository& repository_);

  void                                  AddSubtasksToRepository(Serialized::Task& serializedTask, TaskID& rootID,
                                                                TaskRepository& repository_);

  TaskRepositoryDTO                     DTOFromSerializedTask(const Serialized::Task& task);

  bool                                  FillNewTasksToRepository(Serialized::Storage& serializedStorage,
                                                                TaskRepository& repository);
}

#endif //TASKMANAGER_CORE_PERSISTER_TASKPERSISTERUTILS_H_
