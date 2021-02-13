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
#include <thread>
#include <chrono>
#include "conifg.h"

int main() {
  auto io = std::make_shared<InputOutputConsoleLayer>();

  std::string target_str{config::network::CLIENT_LOCALHOST + ":" + config::network::SERVER_PORT};

  auto channel = grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials());
  int retry_counter = 10;
  while (true){
      if (GRPC_CHANNEL_READY == channel->GetState(true)){
          io->Output("Connected.");
          break;
      }
      if (--retry_counter < 0){
          io->Output("Error. Cannot connect to the server.\n");
          return 0;
      }
      io->Output("Cannot connect to the server. Try to reconnect..\n");
      std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  auto stub = std::make_unique<transport::TaskService::Stub>(channel);


  std::unique_ptr<TaskService> client = std::make_unique<TaskServiceClient>(std::move(stub));

  auto menu = Factory::CreateMenuStateMachine(StatesID::BASE_MENU,
                                              std::make_shared<Context>(*client),*io );

  menu->Execute();

  return 0;
}
