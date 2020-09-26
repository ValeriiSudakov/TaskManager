//
// Created by valeriisudakov on 25.09.20.
//

#include "Persister.h"
#include "Memory_Model/Storage/TaskRepositoryClass.h"
#include "Memory_Model/Task/Task.h"
#include "API/TaskID.h"
#include "API/Priority.h"

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

SerializePriority DataPersister::PriorityToSerializedPriority(const Priority& priority){
  if (Priority::FIRST == priority){
    return SerializePriority::FIRST;
  } else if (Priority::SECOND == priority){
    return SerializePriority::SECOND;
  } else if (Priority::THIRD == priority){
    return SerializePriority::THIRD;
  } else if (Priority::NONE == priority) {
    return SerializePriority::NONE;
  }
}

Priority DataPersister::SerializedPriorityToPriority(const SerializePriority& priority){
  if (SerializePriority::FIRST == priority){
    return Priority::FIRST;
  } else if (SerializePriority::SECOND == priority){
    return Priority::SECOND;
  } else if (SerializePriority::THIRD == priority){
    return Priority::THIRD;
  } else if (SerializePriority::NONE == priority) {
    return Priority::NONE;
  }
}

