//
// Created by valeriisudakov on 26.10.20.
//

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "TaskServiceTransport.pb.h"
#include "API/Service/TaskServiceServer.h"
#include "Repository/RepositoriesFactory/TaskRepositoryFactory.h"
#include "Repository/RepositoryController/TaskRepositoryController.h"

int main(){
  std::string server_address("0.0.0.0:50051");
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
  // Finally assemble the server.
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
  return 0;
}