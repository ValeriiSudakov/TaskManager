
#include "StatesControllers/StateMachineMenu.h"
#include "InputOutpuConsoleLayer.h"

int main(){
  std::unique_ptr<StateMachine> menu = std::make_unique<StateMachineMenu>(
                                    StatesID::BASE_MENU,
                                    std::make_shared<Context>(std::move(std::make_unique<TaskService>(TaskService::Create()))),
                                    std::move(std::make_unique<InputOutpuConsoleLayer>())
                                    );

  menu->Execute();
  return 0;
}