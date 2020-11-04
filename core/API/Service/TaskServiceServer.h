//
// Created by valeriisudakov on 27.10.20.
//

#ifndef TASKMANAGER_CORE_API_SERVICE_TASKSERVICESERVER_H_
#define TASKMANAGER_CORE_API_SERVICE_TASKSERVICESERVER_H_


#include "TaskServiceTransport.pb.h"
#include "TaskServiceTransport.grpc.pb.h"
#include "Repository/RepositoryController/RepositoryController.h"

 class TaskServiceServer : public transport::TaskService::Service{
 public:
  TaskServiceServer(std::unique_ptr<RepositoryController> repositoryFactory)
  : repositoryController_(std::move(repositoryFactory)) { }

 public:
  ::grpc::Status AddTask(::grpc::ServerContext *context, const ::requests::AddTask *request, ::response::AddTask *response) override;
  ::grpc::Status AddSubtask(::grpc::ServerContext *context, const ::requests::AddSubtask *request, ::response::AddSubtask *response) override;
  ::grpc::Status RemoveTask(::grpc::ServerContext *context, const ::requests::RemoveTask *request, ::response::RemoveTask *response) override;
  ::grpc::Status PostponeTask(::grpc::ServerContext *context, const ::requests::PostponeTask *request, ::response::PostponeTask *response) override;
  ::grpc::Status SetComplete(::grpc::ServerContext *context, const ::requests::SetComplete *request, ::response::SetComplete *response) override;

  ::grpc::Status Save(::grpc::ServerContext *context, const ::requests::Save *request, ::response::Save *response) override;
  ::grpc::Status Load(::grpc::ServerContext *context, const ::requests::Load *request, ::response::Load *response) override;

  ::grpc::Status GetTask(::grpc::ServerContext *context, const ::requests::GetTask *request, ::response::GetTask *response) override;
  ::grpc::Status GetSubtasks(::grpc::ServerContext *context, const ::requests::GetSubtasks *request, ::response::GetSubtasks *response) override;
  ::grpc::Status GetTasks(::grpc::ServerContext *context, const ::requests::GetTasks *request, ::response::GetTasks *response) override;
  ::grpc::Status GetTodayTasks(::grpc::ServerContext *context, const ::requests::GetTodayTasks *request, ::response::GetTodayTasks *response) override;
  ::grpc::Status GetWeekTasks(::grpc::ServerContext *context, const ::requests::GetWeekTasks *request, ::response::GetWeekTasks *response) override;
  ::grpc::Status GetTasksByName(::grpc::ServerContext *context, const ::requests::GetTasksByName *request, ::response::GetTasksByName *response) override;
  ::grpc::Status GetTasksByLabel(::grpc::ServerContext *context, const ::requests::GetTasksByLabel *request, ::response::GetTasksByLabel *response) override;
  ::grpc::Status GetTasksByPriority(::grpc::ServerContext *context, const ::requests::GetTasksByPriority *request, ::response::GetTasksByPriority *response) override;

 private:
  std::unique_ptr<RepositoryController> repositoryController_;
 };


#endif //TASKMANAGER_CORE_API_SERVICE_TASKSERVICESERVER_H_
