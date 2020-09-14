
#include "StatesControllers/StateMachineMenu.h"
#include "InputOutputConsoleLayer.h"
#include "States/StatesID.h"

#include "Factory/Factory.h"

int main(){
  auto io = std::make_shared<InputOutputConsoleLayer>();
  auto menu = Factory::CreateMenuStateMachine(StatesID::BASE_MENU,
                                               std::make_shared<Context>(std::move(std::make_unique<TaskService>(
                                                                                                 TaskService::Create()))),
                                                 io
                                                 );
  menu->Execute();
  return 0;
}