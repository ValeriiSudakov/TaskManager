//
// Created by valeriisudakov on 29.09.20.
//

#ifndef TASKMANAGER_CORE_PERSISTER_DATAPERSISTER_H_
#define TASKMANAGER_CORE_PERSISTER_DATAPERSISTER_H_
#include "SerializedModel.pb.h"
#include <string>
#include <memory>

class TaskEntity;
class TaskID;
class TaskRepository;
enum class Priority;

namespace DataPersister{
  class Persister{
   public:
    virtual ~Persister() = default;

    virtual bool                        Save() = 0;
    virtual bool                        Load() = 0;
  };


  SerializePriority                     PriorityToSerializedPriority(const Priority& priority);
  Priority                              SerializedPriorityToPriority(const SerializePriority& priority);
}

#endif //TASKMANAGER_CORE_PERSISTER_DATAPERSISTER_H_
