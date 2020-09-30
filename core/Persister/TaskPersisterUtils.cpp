//
// Created by valeriisudakov on 30.09.20.
//

#include "TaskPersisterUtils.h"


std::unique_ptr<Serialized::Task> PersisterUtils::SerializedTaskFromDTO(const TaskRepositoryDTO& taskDTO){
  auto task = std::make_unique<Serialized::Task>();

  task->set_name(taskDTO.GetName());
  task->set_label(taskDTO.GetLabel());
  task->set_priority(PriorityToSerializedPriority(taskDTO.GetPriority()));
  task->set_date(taskDTO.GetDate().Get().day_number());
  task->set_complete(taskDTO.Complete());

  return  std::move(task);
}


TaskRepositoryDTO PersisterUtils::DTOFromSerializedTask(const Serialized::Task& task){
  auto dto = TaskRepositoryDTO::Create(task.name(), task.label(),
                                       SerializedPriorityToPriority(task.priority()),
                                       Date(boost::gregorian::date(task.date())),
                                       task.complete(), TaskID(), TaskID());
  assert(dto.has_value());
  return dto.value();
}

void AddSubtasksToRepository(Serialized::Task& serializedTask, TaskID& rootID, TaskRepository& repository_){
  if (serializedTask.subtasks().empty()){
    return;
  }

  for (auto& subtask : serializedTask.subtasks()){
    auto subtaskDTO = PersisterUtils::DTOFromSerializedTask(subtask);

    auto addTaskResult = repository_.AddSubtask(rootID, subtaskDTO);

    auto nonConstTask = subtask;
    AddSubtasksToRepository(nonConstTask, addTaskResult.id_.value(), repository_);
  }
}

void PersisterUtils::AddSubtasks(Serialized::Task& serializedTask, TaskRepositoryDTO& task, TaskRepository& repository_){
  auto subtasks = repository_.GetSubtask(task.GetID());
  if (subtasks.empty()){
    return;
  }
  for (auto& task : subtasks){
    auto newSubtask = std::move(SerializedTaskFromDTO(task));

    auto* allocatedTask = serializedTask.add_subtasks();
    FillTask(*allocatedTask, *newSubtask);

    AddSubtasks(*allocatedTask, task, repository_);
  }
}

void PersisterUtils::FillTask(Serialized::Task& newTask, Serialized::Task& data){
  newTask.set_name(data.name());
  newTask.set_label(data.label());
  newTask.set_priority(data.priority());
  newTask.set_date(data.date());
  newTask.set_complete(data.complete());
}

Serialized::Priority PersisterUtils::PriorityToSerializedPriority(const Priority& priority){
  if (Priority::FIRST == priority){
    return Serialized::Priority::FIRST;
  } else if (Priority::SECOND == priority){
    return Serialized::Priority::SECOND;
  } else if (Priority::THIRD == priority){
    return Serialized::Priority::THIRD;
  } else if (Priority::NONE == priority) {
    return Serialized::Priority::NONE;
  }
}

Priority PersisterUtils::SerializedPriorityToPriority(const Serialized::Priority& priority){
  if (Serialized::Priority::FIRST == priority){
    return Priority::FIRST;
  } else if (Serialized::Priority::SECOND == priority){
    return Priority::SECOND;
  } else if (Serialized::Priority::THIRD == priority){
    return Priority::THIRD;
  } else if (Serialized::Priority::NONE == priority) {
    return Priority::NONE;
  }
}

