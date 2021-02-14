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

    io.Output("Starting server on: " + server_address + "\n");

    server_mutex_.lock();

    server_ = std::move(builder.BuildAndStart());
    if (!server_){
      server_mutex_.unlock();
      io.Output(std::string{"Error. Server was not created. Shutting down\n"});
      return;
    } else {
      io.Output(std::string{"Server is listening on: " + server_address + "\n"});
    }
    server_mutex_.unlock();
    server_->Wait();
  }
  void Stop(){
    server_mutex_.lock();
    server_->Shutdown();
    server_mutex_.unlock();
  }
 private:
  InputOutputConsoleLayer io_;
  std::mutex server_mutex_;
  std::unique_ptr<grpc::Server> server_;
};


int main(){
  InputOutputConsoleLayer io;
  auto server_controller = std::make_unique<ServerController>(io);

  auto server_thread = std::make_unique<std::thread>(std::bind(&ServerController::Start, server_controller.get(), io));

  std::this_thread::sleep_for(std::chrono::seconds(1));
  io.Output("Inpuq 'q' to quit\n");

  while(io.Input() != "q");

  io.Output("Shutdown server...\n");
  server_controller->Stop();

  if (server_thread && server_thread->joinable()){
    server_thread->join();
    io.Output(std::string{"Server stopped working.\n"});
  }

  return 0;
}