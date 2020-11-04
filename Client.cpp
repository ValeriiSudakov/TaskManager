//
// Created by valeriisudakov on 26.10.20.
//


#include <grpcpp/grpcpp.h>

#include "TaskServiceTransport.grpc.pb.h"
#include "API/Service/TaskServiceClient.h"

#include "StatesControllers/StateMachineMenu.h"
#include "InputOutputConsoleLayer.h"
#include "States/StatesID.h"
#include "Factory/Factory.h"

int main() {
  std::string target_str;
  target_str = "localhost:50051";
  auto stub = std::make_unique<transport::TaskService::Stub>(grpc::CreateChannel(
                                                            target_str,
                                                            grpc::InsecureChannelCredentials()));

  auto io = std::make_shared<InputOutputConsoleLayer>();

  // Check connection to the server
  // make simple request to check
  {
    auto context = std::make_unique<grpc::ClientContext>();
    requests::AddTask request;
    response::AddTask response;
    auto result = stub->AddTask(context.get(), request, &response);
    if (!result.ok()){
      io->Output("Error. Cannot connect to the server.\n");
      return 0;
    }
    io->Output("Connected to the server successfully.\n");
  }

  std::unique_ptr<TaskService> client = std::make_unique<TaskServiceClient>(std::move(stub));

  auto menu = Factory::CreateMenuStateMachine(StatesID::BASE_MENU,
                                              std::make_shared<Context>(*client),*io );

  menu->Execute();

  return 0;
}
