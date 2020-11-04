//
// Created by valeriisudakov on 30.09.20.
//

#include "TaskPersisterUtils.h"
#include "Persister/TaskPersister.h"
#include <memory>

std::unique_ptr<Persister> persister_utils::Create(TaskRepository &repository, std::fstream &stream) {
  return std::move(std::make_unique<TaskPersister>(repository, stream));
}

void persister_utils::SerializedTaskFromDTO(const TaskRepositoryDTO& taskDTO,
                                            proto::Task& task){
  task.set_name(taskDTO.GetName());
  task.set_label(taskDTO.GetLabel());
  task.set_priority(PriorityToSerializedPriority(taskDTO.GetPriority()));
  task.mutable_date()->set_value(taskDTO.GetDate().Get().day_number());
  task.set_complete(taskDTO.Complete());
}


std::optional<TaskRepositoryDTO> persister_utils::DTOFromSerializedTask(const proto::Task& task){
  auto dto = TaskRepositoryDTO::Create(task.name(), task.label(),
                                       SerializedPriorityToPriority(task.priority()),
                                       Date(boost::gregorian::date(task.date().value())),
                                       task.complete(), TaskID(), TaskID());
  return dto;
}

void persister_utils::AddSubtasksToRepository(const proto::Task& serializedTask, TaskID& rootID, TaskRepository& repository_){
  if (serializedTask.subtasks().empty()){
    return;
  }

  for (auto& subtask : serializedTask.subtasks()){
    auto subtaskDTO    = persister_utils::DTOFromSerializedTask(subtask);

    auto addTaskResult = repository_.AddSubtask(rootID, subtaskDTO.value());

    AddSubtasksToRepository(subtask, addTaskResult.id_.value(), repository_);
  }
}

void persister_utils::AddSubtasks(proto::Task& serializedTask, TaskRepositoryDTO& task, TaskRepository& repository_){
  auto subtasks = repository_.GetSubtask(task.GetID());
  if (subtasks.empty()){
    return;
  }
  for (auto& subtask : subtasks){
    proto::Task* allocatedTask = serializedTask.add_subtasks();
    SerializedTaskFromDTO(subtask, *allocatedTask);
    AddSubtasks(*allocatedTask, subtask, repository_);
  }
}

proto::Priority persister_utils::PriorityToSerializedPriority(const Priority& priority){
  if (Priority::FIRST == priority){
    return proto::Priority::FIRST;
  } else if (Priority::SECOND == priority){
    return proto::Priority::SECOND;
  } else if (Priority::THIRD == priority){
    return proto::Priority::THIRD;
  } else if (Priority::NONE == priority) {
    return proto::Priority::NONE;
  }
}

Priority persister_utils::SerializedPriorityToPriority(const proto::Priority& priority){
  if (proto::Priority::FIRST == priority){
    return Priority::FIRST;
  } else if (proto::Priority::SECOND == priority){
    return Priority::SECOND;
  } else if (proto::Priority::THIRD == priority){
    return Priority::THIRD;
  } else if (proto::Priority::NONE == priority) {
    return Priority::NONE;
  }
}

