//
// Created by valeriisudakov on 27.10.20.
//

#include "TaskServiceServer.h"
#include "TaskPersisterUtils.h"
#include "TaskServiceServerUtils.h"
#include "utils.h"

::grpc::Status TaskServiceServer::AddTask(::grpc::ServerContext *context,
                                          const ::requests::AddTask *request,
                                          ::response::AddTask *response) {
  auto dto = task_service_server_utils::ToTaskRepositoryDTO(request->taskdata());
  if (!dto.has_value()){
    response->mutable_result()->set_success(false);
    response->mutable_result()->set_error(transport::Error::TASK_IS_DAMAGED);
    return grpc::Status::OK;
  }
  auto addingNewTask = repositoryController_->Get()->AddTask(dto.value());
  auto result = task_service_server_utils::ToTransport(addingNewTask);

  if (addingNewTask.success_){
    response->mutable_result()->set_success(true);
    response->mutable_result()->mutable_id()->set_value(result.id().value());
  } else {
    response->mutable_result()->set_success(false);
    response->mutable_result()->set_error(result.error());
  }
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::AddSubtask(::grpc::ServerContext *context,
                                             const ::requests::AddSubtask *request,
                                             ::response::AddSubtask *response) {
  auto dto = task_service_server_utils::ToTaskRepositoryDTO(request->subtaskdata());
  if (!dto.has_value()){
    response->mutable_result()->set_success(false);
    response->mutable_result()->set_error(transport::Error::TASK_IS_DAMAGED);
    return grpc::Status::OK;
  }
  auto addingNewTask = repositoryController_->Get()->AddSubtask(TaskID(request->rootid().value()), dto.value());
  auto result = task_service_server_utils::ToTransport(addingNewTask);

  if (addingNewTask.success_){
    response->mutable_result()->set_success(true);
    response->mutable_result()->mutable_id()->set_value(result.id().value());
  } else {
    response->mutable_result()->set_success(false);
    response->mutable_result()->set_error(result.error());
  }
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::RemoveTask(::grpc::ServerContext *context,
                                             const ::requests::RemoveTask *request,
                                             ::response::RemoveTask *response) {
  auto result = repositoryController_->Get()->RemoveTask(TaskID(request->id().value()));
  response->set_success(result);
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::Save(::grpc::ServerContext *context,
                                       const ::requests::Save *request,
                                       ::response::Save *response) {
  auto result = repositoryController_->Save(request->filename());
  response->set_success(result);
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::Load(::grpc::ServerContext *context,
                                       const ::requests::Load *request,
                                       ::response::Load *response) {
  auto result = repositoryController_->Load(request->filename());
  response->set_success(result);
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::PostponeTask(::grpc::ServerContext *context,
                                               const ::requests::PostponeTask *request,
                                               ::response::PostponeTask *response) {
  auto result = repositoryController_->Get()->PostponeTask(TaskID(request->id().value()),
                                                           boost::gregorian::date(request->date().value()));
  response->set_success(result);
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::SetComplete(::grpc::ServerContext *context,
                                              const ::requests::SetComplete *request,
                                              ::response::SetComplete *response) {
  auto result = repositoryController_->Get()->SetTaskComplete(TaskID(request->id().value()));
  response->set_success(result);
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::GetTask(::grpc::ServerContext *context,
                                          const ::requests::GetTask *request,
                                          ::response::GetTask *response) {
  auto task = repositoryController_->Get()->GetTask(TaskID(request->id().value()));
  response->clear_task();
  if (task.has_value()){
    auto transportTask = task_service_server_utils::ToTransport(task.value());
    task_service_server_utils::FillTransportTask(transportTask, response->mutable_task());
  }
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::GetSubtasks(::grpc::ServerContext *context,
                                              const ::requests::GetSubtasks *request,
                                              ::response::GetSubtasks *response) {
  auto tasks = repositoryController_->Get()->GetSubtask(TaskID(request->id().value()));
  for (const auto& task : tasks){
    auto newTask = response->add_tasks();
    task_service_server_utils::FillTransportTask(task_service_server_utils::ToTransport(task), newTask);
  }
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::GetTasks(::grpc::ServerContext *context,
                                           const ::requests::GetTasks *request,
                                           ::response::GetTasks *response) {
  auto tasks = repositoryController_->Get()->GetTasks();
  if (request->sortbypriority()){
    task_service_server_utils::SortTasks(tasks);
  }
  for (const auto& task : tasks){
    auto newTask = response->add_tasks();
    task_service_server_utils::FillTransportTask(task_service_server_utils::ToTransport(task), newTask);
  }
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::GetTodayTasks(::grpc::ServerContext *context,
                                                const ::requests::GetTodayTasks *request,
                                                ::response::GetTodayTasks *response) {
  auto tasks = repositoryController_->Get()->GetTodayTasks(request->sortbypriority());
  for (const auto& task : tasks){
    auto newTask = response->add_tasks();
    task_service_server_utils::FillTransportTask(task_service_server_utils::ToTransport(task), newTask);
  }
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::GetWeekTasks(::grpc::ServerContext *context,
                                               const ::requests::GetWeekTasks *request,
                                               ::response::GetWeekTasks *response) {
  auto tasks = repositoryController_->Get()->GetWeekTasks(request->sortbypriority());
  for (const auto& task : tasks){
    auto newTask = response->add_tasks();
    task_service_server_utils::FillTransportTask(task_service_server_utils::ToTransport(task), newTask);
  }
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::GetByDateTasks(::grpc::ServerContext *context,
                                                 const ::requests::GetByDateTasks *request,
                                                 ::response::GetByDateTasks *response) {
  auto tasks = repositoryController_->Get()->GetTasksByDate(boost::gregorian::date(request->date().value()), request->sortbypriority());
  for (const auto& task : tasks) {
    auto newTask = response->add_tasks();
    task_service_server_utils::FillTransportTask(task_service_server_utils::ToTransport(task), newTask);
  }
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::GetTasksByName(::grpc::ServerContext *context,
                                                 const ::requests::GetTasksByName *request,
                                                 ::response::GetTasksByName *response) {
  auto tasks = repositoryController_->Get()->GetTasksByName(request->name(), request->sortbypriority());
  for (const auto& task : tasks){
    auto newTask = response->add_tasks();
    task_service_server_utils::FillTransportTask(task_service_server_utils::ToTransport(task), newTask);
  }
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::GetTasksByLabel(::grpc::ServerContext *context,
                                                  const ::requests::GetTasksByLabel *request,
                                                  ::response::GetTasksByLabel *response) {
  auto tasks = repositoryController_->Get()->GetTasksByLabel(request->label(), request->sortbypriority());
  auto responseTasks = response->tasks();
  for (const auto& task : tasks){
    auto newTask = response->add_tasks();
    task_service_server_utils::FillTransportTask(task_service_server_utils::ToTransport(task), newTask);
  }
  return grpc::Status::OK;
}

::grpc::Status TaskServiceServer::GetTasksByPriority(::grpc::ServerContext *context,
                                                     const ::requests::GetTasksByPriority *request,
                                                     ::response::GetTasksByPriority *response) {
  auto tasks = repositoryController_->Get()->GetTasksByPriority(SerializedPriorityToPriority(request->priority()));
  for (const auto& task : tasks){
    auto newTask = response->add_tasks();
    task_service_server_utils::FillTransportTask(task_service_server_utils::ToTransport(task), newTask);
  }
  return grpc::Status::OK;
}
