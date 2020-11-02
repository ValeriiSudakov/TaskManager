//
// Created by valeriisudakov on 29.10.20.
//

#include "TaskServiceClient.h"
#include "API/Utils/TaskServiceClientUtils.h"
#include "API/Utils/TaskServiceServerUtils.h"
#include "Persister/Utils/TaskPersisterUtils.h"

AddTaskResult TaskServiceClient::AddTask(const TaskServiceDTO &task) {
  grpc::ClientContext context;

  requests::AddTask request;
  task_service_client_utils::FillTransportTaskFromDTO(task, request.mutable_taskdata());

  response::AddTask response;
  auto result = server_requests_maker_->AddTask(&context, request, &response);

  if (result.ok()){
    if (response.result().success()){
      return AddTaskResult::Success(response.result().id().value());
    }
    return AddTaskResult::Failed(task_service_client_utils::FromTransportError(response.result().error()));
  }
  return AddTaskResult::Failed(AddTaskResult::ErrorType::BAD_CONNECTION);
}

AddTaskResult TaskServiceClient::AddSubtask(const TaskID &rootTaskID, const TaskServiceDTO &subtask) {
  grpc::ClientContext context;

  requests::AddSubtask request;
  task_service_client_utils::FillTransportTaskFromDTO(subtask, request.mutable_subtaskdata());
  request.mutable_rootid()->set_value(rootTaskID.Get());

  response::AddSubtask response;
  auto result = server_requests_maker_->AddSubtask(&context, request, &response);

  if (result.ok()){
    if (response.result().success()){
      return AddTaskResult::Success(response.result().id().value());
    }
    return AddTaskResult::Failed(task_service_client_utils::FromTransportError(response.result().error()));
  }
  return AddTaskResult::Failed(AddTaskResult::ErrorType::BAD_CONNECTION);
}

bool TaskServiceClient::Load(const std::string &filename) {
  grpc::ClientContext context;

  requests::Load request;
  request.set_filename(filename);

  response::Load response;
  auto result = server_requests_maker_->Load(&context, request, &response);
  if (result.ok()){
    return response.success();
  }
  return false;
}

bool TaskServiceClient::Save(const std::string &filename) {
  grpc::ClientContext context;

  requests::Save request;
  request.set_filename(filename);

  response::Save response;
  auto result = server_requests_maker_->Save(&context, request, &response);
  if (result.ok()){
    return response.success();
  }
  return false;
}

bool TaskServiceClient::RemoveTask(const TaskID &ID) {
  grpc::ClientContext context;

  requests::RemoveTask request;
  request.mutable_id()->set_value(ID.Get());

  response::RemoveTask response;
  auto result = server_requests_maker_->RemoveTask(&context, request, &response);
  if (result.ok()){
    return response.success();
  }
  return false;
}

bool TaskServiceClient::PostponeTask(const TaskID &ID, const Date &date) {
  grpc::ClientContext context;

  requests::PostponeTask request;
  request.mutable_id()->set_value(ID.Get());
  request.mutable_date()->set_value(date.Get().day_number());

  response::PostponeTask response;
  auto result = server_requests_maker_->PostponeTask(&context, request, &response);
  if (result.ok()){
    return response.success();
  }
  return false;
}

bool TaskServiceClient::SetTaskComplete(const TaskID &ID) {
  grpc::ClientContext context;

  requests::SetComplete request;
  request.mutable_id()->set_value(ID.Get());

  response::SetComplete response;
  auto result = server_requests_maker_->SetComplete(&context, request, &response);
  if (result.ok()){
    return response.success();
  }
  return false;
}

std::optional<TaskServiceDTO> TaskServiceClient::GetTask(const TaskID &id) const {
  grpc::ClientContext context;

  requests::GetTask request;
  request.mutable_id()->set_value(id.Get());

  response::GetTask response;
  auto result = server_requests_maker_->GetTask(&context, request, &response);
  if (result.ok()){
    if (!response.has_task()){
      return std::nullopt;
    }
    return task_service_client_utils::FromTransportTask(response.task());
  }
  return std::nullopt;
}

std::vector<TaskServiceDTO> TaskServiceClient::GetSubtask(const TaskID &id) const {
  grpc::ClientContext context;

  requests::GetSubtasks request;
  request.mutable_id()->set_value(id.Get());

  response::GetSubtasks response;
  auto result = server_requests_maker_->GetSubtasks(&context, request, &response);
  std::vector<TaskServiceDTO> tasks;
  if (result.ok()) {
    for (const auto& task : response.tasks()){
      tasks.push_back(task_service_client_utils::FromTransportTask(task).value());
    }
  }
  return tasks;
}

std::vector<TaskServiceDTO> TaskServiceClient::GetTasks(bool byPriority) const {
  grpc::ClientContext context;

  requests::GetTasks request;
  request.set_sortbypriority(byPriority);

  response::GetTasks response;
  auto result = server_requests_maker_->GetTasks(&context, request, &response);
  std::vector<TaskServiceDTO> tasks;
  if (result.ok()) {
    for (const auto& task : response.tasks()){
      tasks.push_back(task_service_client_utils::FromTransportTask(task).value());
    }
  }
  return tasks;
}
std::vector<TaskServiceDTO> TaskServiceClient::GetTodayTasks(bool byPriority) const {
  grpc::ClientContext context;

  requests::GetTodayTasks request;
  request.set_sortbypriority(byPriority);

  response::GetTodayTasks response;
  auto result = server_requests_maker_->GetTodayTasks(&context, request, &response);
  std::vector<TaskServiceDTO> tasks;
  if (result.ok()) {
    for (const auto& task : response.tasks()){
      tasks.push_back(task_service_client_utils::FromTransportTask(task).value());
    }
  }
  return tasks;
}
std::vector<TaskServiceDTO> TaskServiceClient::GetWeekTasks(bool byPriority) const {
  grpc::ClientContext context;

  requests::GetWeekTasks request;
  request.set_sortbypriority(byPriority);

  response::GetWeekTasks response;
  auto result = server_requests_maker_->GetWeekTasks(&context, request, &response);
  std::vector<TaskServiceDTO> tasks;
  if (result.ok()) {
    for (const auto& task : response.tasks()){
      tasks.push_back(task_service_client_utils::FromTransportTask(task).value());
    }
  }
  return tasks;
}
std::vector<TaskServiceDTO> TaskServiceClient::GetTasksByLabel(const std::string &label, bool byPriority) const {
  grpc::ClientContext context;

  requests::GetTasksByLabel request;
  request.set_sortbypriority(byPriority);
  request.set_label(label);

  response::GetTasksByLabel response;
  auto result = server_requests_maker_->GetTasksByLabel(&context, request, &response);
  std::vector<TaskServiceDTO> tasks;
  if (result.ok()) {
    for (const auto& task : response.tasks()){
      tasks.push_back(task_service_client_utils::FromTransportTask(task).value());
    }
  }
  return tasks;
}
std::vector<TaskServiceDTO> TaskServiceClient::GetTasksByName(const std::string &name, bool byPriority) const {
  grpc::ClientContext context;

  requests::GetTasksByName request;
  request.set_sortbypriority(byPriority);
  request.set_name(name);

  response::GetTasksByName response;
  auto result = server_requests_maker_->GetTasksByName(&context, request, &response);
  std::vector<TaskServiceDTO> tasks;
  if (result.ok()) {
    for (const auto& task : response.tasks()){
      tasks.push_back(task_service_client_utils::FromTransportTask(task).value());
    }
  }
  return tasks;
}

std::vector<TaskServiceDTO> TaskServiceClient::GetTasksByPriority(const Priority &priority) const {
  grpc::ClientContext context;

  requests::GetTasksByPriority request;
  request.set_priority(persister_utils::PriorityToSerializedPriority(priority));
  response::GetTasksByPriority response;
  auto result = server_requests_maker_->GetTasksByPriority(&context, request, &response);
  std::vector<TaskServiceDTO> tasks;
  if (result.ok()) {
    for (const auto& task : response.tasks()){
      tasks.push_back(task_service_client_utils::FromTransportTask(task).value());
    }
  }
  return tasks;
}
