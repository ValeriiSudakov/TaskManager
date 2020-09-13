
#include "StatesControllers/StateMachineMenu.h"
#include "InputOutpuConsoleLayer.h"
#include "States/StatesID.h"

#include "Factory/Factory.h"

int main(){
  auto menu = Factory::CreateMenuStateMachine(StatesID::BASE_MENU,
                                               std::make_shared<Context>(std::move(std::make_unique<TaskService>(
                                                                                                 TaskService::Create()))),
                                                 std::move(std::make_unique<InputOutpuConsoleLayer>())
                                                 );
  menu->Execute();
  return 0;
}