//
// Created by valeriisudakov on 26.10.20.
//

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "TaskServiceTransport.pb.h"
#include "InputOutputConsoleLayer.h"
#include "API/Service/TaskServiceServer.h"
#include "Repository/RepositoriesFactory/TaskRepositoryFactory.h"
#include "Repository/RepositoryController/TaskRepositoryController.h"

#include "conifg.h"

int main(){
  InputOutputConsoleLayer io;

  std::string server_address(config::network::SERVER_LOCALHOST + ":" + config::network::SERVER_PORT);
  std::unique_ptr<RepositoriesFactory> factory = std::make_unique<TaskRepositoryFactory>();
  std::unique_ptr<RepositoryController> controller = std::make_unique<TaskRepositoryController>(std::move(factory));
  TaskServiceServer taskServiceServer(std::move(controller));

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  grpc::ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&taskServiceServer);

  io.Output("Starting server on: " + server_address);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  server->Wait();
  return 0;
}