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

  void                                  SerializedTaskFromDTO(const TaskRepositoryDTO& taskDTO,
                                                              Serialized::Task& task);

  void                                  AddSubtasks(Serialized::Task& serializedTask, TaskRepositoryDTO& task,
                                                    TaskRepository& repository_);

  void                                  AddSubtasksToRepository(const Serialized::Task& serializedTask, TaskID& rootID,
                                                                TaskRepository& repository_);

  TaskRepositoryDTO                     DTOFromSerializedTask(const Serialized::Task& task);
}

#endif //TASKMANAGER_CORE_PERSISTER_TASKPERSISTERUTILS_H_
