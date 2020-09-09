
#include "StatesControllers/StateMachineMenu.h"
#include "IO_Layer.h"

int main(){

  //std::unique_ptr<StateMachine> menu = std::make_unique<StateMachineMenu>
  StateMachineMenu menu(
      StatesID::Menu,
      std::make_shared<Context>(std::move(std::make_unique<TaskService>(TaskService::Create()))),
      std::move(std::make_unique<IO_Layer>())
  );

  menu.Execute();
  return 0;
}