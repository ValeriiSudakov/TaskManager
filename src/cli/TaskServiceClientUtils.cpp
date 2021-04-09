//
// Created by valeriisudakov on 29.10.20.
//

#include "TaskServiceClientUtils.h"
#include "TaskPersisterUtils.h"
#include "utils.h"

namespace task_service_client_utils {

void FillTransportTaskFromDTO(const TaskServiceDTO& source, transport::Task* destination) {
  destination->set_name(source.GetName());
  destination->set_label(source.GetLabel());
  destination->set_priority(persister_utils::PriorityToSerializedPriority(source.GetPriority()));
  destination->mutable_date()->set_value(source.GetDate().Get().day_number());
  destination->set_complete(source.IsTaskComplete());
  destination->mutable_id()->set_value(source.GetTaskId().Get());
}

AddTaskResult::ErrorType FromTransportError(const transport::Error &error) {
  if (transport::Error::NOT_FOUND_PARENT_TASK == error){
    return AddTaskResult::ErrorType::NOT_FOUND_PARENT_TASK;
  } else if (transport::Error::TASK_IS_DAMAGED == error){
    return AddTaskResult::ErrorType::TASK_IS_DAMAGED;
  } else if (transport::Error::NOT_ENOUGH_FREE_MEMORY == error){
    return AddTaskResult::ErrorType::NOT_ENOUGH_FREE_MEMORY;
  }
  return AddTaskResult::ErrorType::UNKNOWN_ERROR_STATE;
}

std::optional<TaskServiceDTO> FromTransportTask(const transport::Task& source) {
  auto dto = TaskServiceDTO::Create(source.name(), source.label(),
                                              SerializedPriorityToPriority(source.priority()),
                                              boost::gregorian::date(source.date().value()),
                                              source.complete(), TaskID(source.id().value()));
  return dto.has_value() ? dto : std::nullopt;
}

} //task_service_client_utils