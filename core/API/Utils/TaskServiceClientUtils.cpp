//
// Created by valeriisudakov on 29.10.20.
//

#include "TaskServiceClientUtils.h"
#include "Persister/Utils/TaskPersisterUtils.h"
void task_service_client_utils::FillTransportTaskFromDTO(const TaskServiceDTO& source, transport::Task* destination) {
  destination->set_name(source.GetName());
  destination->set_label(source.GetLabel());
  destination->set_priority(persister_utils::PriorityToSerializedPriority(source.GetPriority()));
  destination->mutable_date()->set_value(source.GetDate().Get().day_number());
  destination->set_complete(source.IsTaskComplete());
  destination->mutable_id()->set_value(source.GetTaskId().Get());
}

AddTaskResult::ErrorType task_service_client_utils::FromTransportError(const transport::Error &error) {
  if (transport::Error::NOT_FOUND_PARENT_TASK == error){
    return AddTaskResult::ErrorType::NOT_FOUND_PARENT_TASK;
  } else if (transport::Error::TASK_IS_DAMAGED == error){
    return AddTaskResult::ErrorType::TASK_IS_DAMAGED;
  } else if (transport::Error::NOT_ENOUGH_FREE_MEMORY == error){
    return AddTaskResult::ErrorType::NOT_ENOUGH_FREE_MEMORY;
  }
}

std::optional<TaskServiceDTO> task_service_client_utils::FromTransportTask(const transport::Task& source) {
  auto dto = TaskServiceDTO::Create(source.name(), source.label(),
                                              persister_utils::SerializedPriorityToPriority(source.priority()),
                                              boost::gregorian::date(source.date().value()),
                                              source.complete(), TaskID(source.id().value()));
  return dto.has_value() ? dto : std::nullopt;
}