//
// Created by valeriisudakov on 27.10.20.
//

#include "TaskServiceServerUtils.h"
#include "Persister/Utils/TaskPersisterUtils.h"

void task_service_server_utils::SortTasks(std::vector<TaskRepositoryDTO> &tasks) {
  std::sort(tasks.begin(), tasks.end(),
              [](const TaskRepositoryDTO& task1, const TaskRepositoryDTO& task2){
                  return task1.GetPriority() < task2.GetPriority();
                });
}

void task_service_server_utils::FillTransportTask(const transport::Task &source, transport::Task *destination) {
  destination->set_name(source.name());
  destination->set_label(source.label());
  destination->set_priority(source.priority());
  destination->mutable_date()->set_value(source.date().value());
  destination->set_complete(source.complete());
  destination->mutable_id()->set_value(source.id().value());
}

transport::Task task_service_server_utils::ToTransport(const TaskRepositoryDTO& task) {
  transport::Task resultTask;
  resultTask.set_name(task.GetName());
  resultTask.set_label(task.GetLabel());
  resultTask.set_priority(persister_utils::PriorityToSerializedPriority(task.GetPriority()));
  resultTask.mutable_date()->set_value(task.GetDate().Get().day_number());
  resultTask.set_complete(task.Complete());
  resultTask.mutable_id()->set_value(task.GetID().Get());
  return resultTask;
}

transport::AddTaskResult task_service_server_utils::ToTransport(const AddTaskResult& result) {
  transport::AddTaskResult transportResult;
  transportResult.mutable_id()->set_value(result.id_->Get());
  transportResult.set_success(result.success_);
  if (result.error_.has_value()) {
    transportResult.set_error(task_service_server_utils::ToTransport(result.error_.value()));
  }
  return transportResult;
}

transport::Error task_service_server_utils::ToTransport(const AddTaskResult::ErrorType& error) {
  if (AddTaskResult::ErrorType::NOT_FOUND_PARENT_TASK == error){
    return transport::Error::NOT_FOUND_PARENT_TASK;
  } else if (AddTaskResult::ErrorType::TASK_IS_DAMAGED == error){
    return transport::Error::TASK_IS_DAMAGED;
  } else if (AddTaskResult::ErrorType::NOT_ENOUGH_FREE_MEMORY == error){
    return transport::Error::NOT_ENOUGH_FREE_MEMORY;
  }
  return transport::Error::UNKNOWN_ERROR_STATE;
}

std::optional<TaskRepositoryDTO> task_service_server_utils::ToTaskRepositoryDTO(const transport::Task &task) {
  auto DTO = TaskRepositoryDTO::Create(task.name(), task.label(),
                                       persister_utils::SerializedPriorityToPriority(task.priority()),
                                       boost::gregorian::date(task.date().value()),
                                       task.complete(), TaskID(task.id().value()),
                                TaskID(0));
  return DTO;
}
