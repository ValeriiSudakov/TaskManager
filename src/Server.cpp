//
// Created by valeriisudakov on 26.10.20.
//

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include <future>

#include "TaskServiceTransport.pb.h"
#include "InputOutputConsoleLayer.h"
#include "API/Service/TaskServiceServer.h"
#include "Repository/RepositoriesFactory/TaskRepositoryFactory.h"
#include "Repository/RepositoryController/TaskRepositoryController.h"

#include "conifg.h"

class ServerController{
 public:
  ServerController(InputOutputConsoleLayer& io) : io_(io){}
  ~ServerController(){
    Stop();
  }
 public:
  void Start(InputOutputConsoleLayer io){
    server_address_ = config::network::SERVER_LOCALHOST + ":" + config::network::SERVER_PORT;

    std::unique_ptr<RepositoriesFactory> factory = std::make_unique<TaskRepositoryFactory>();
    std::unique_ptr<RepositoryController> controller = std::make_unique<TaskRepositoryController>(std::move(factory));
    TaskServiceServer taskServiceServer(std::move(controller));

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    grpc::ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&taskServiceServer);

    io_.Output("Starting server on: " + server_address_ + "\n");

    server_ = std::move(builder.BuildAndStart());

    if (!server_){
      io.Output(std::string{"Error. Server was not created. Shutting down\n"});
      return;
    } else {
      io.Output(std::string{"Server is listening on: " + server_address_ + "\n"});
    }
    server_->Wait();
  }
  void Stop(){
    server_->Shutdown();
  }
 private:
  std::string server_address_;
  InputOutputConsoleLayer io_;
  std::unique_ptr<grpc::Server> server_;
};


int main(){
  InputOutputConsoleLayer io;
  auto server_controller = std::make_unique<ServerController>(io);

  auto server_thread = std::make_unique<std::thread>(std::bind(&ServerController::Start, server_controller.get(), io));

  std::this_thread::sleep_for(std::chrono::seconds(1));
  io.Output("Input 'q' to quit\n");

  while(io.Input() != "q");

  if (server_thread && server_thread->joinable()){
    io.Output("Shutdown server...\n");
    server_controller->Stop();

    server_thread->join();
    io.Output(std::string{"Server stopped working.\n"});
  }

  return 0;
}