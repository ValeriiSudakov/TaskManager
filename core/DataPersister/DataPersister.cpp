//
// Created by valeriisudakov on 25.09.20.
//

#include "DataPersister.h"
#include "Memory_Model/Storage/TaskRepositoryClass.h"
#include "Memory_Model/Task/Task.h"
#include "API/TaskID.h"
#include "API/Priority.h"

void DataPersister::AddSerializedTask(SerializedStorage& storage, std::unique_ptr<SerializedTaskEntity>& task){
  auto* addTask = storage.add_tasks();
  addTask->set_allocated_task(task->release_task());
  addTask->set_id(task->id());
  addTask->set_rootid(task->rootid());
  addTask->set_complete(task->complete());
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

std::unique_ptr<SerializedTaskEntity> DataPersister::MakeSerializeTask(const TaskEntity& task,
                                                        std::map<TaskID, TaskID>& idMapping){
  auto newTask = std::make_unique<SerializedTask>();
  newTask->set_name(task.GetName());
  newTask->set_label(task.GetLabel());
  newTask->set_priority(PriorityToSerializedPriority(task.GetPriority()));
  newTask->set_date(task.GetDueDate().Get().day_number());

  auto newTaskEntity = std::make_unique<SerializedTaskEntity>();
  newTaskEntity->set_allocated_task(newTask.release());

  auto newID = idMapping[task.GetId()];
  newTaskEntity->set_id(newID.Get());

  auto newParentID = idMapping[task.GetParentId()];
  newTaskEntity->set_rootid(newParentID.Get());

  newTaskEntity->set_complete(task.IsComplete());

  return std::move(newTaskEntity);
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

