
#include "StatesControllers/StateMachineMenu.h"
#include "IO_Layer.h"

int main(){
  StateMachineMenu menu(
      StatesID::BaseMenu,
      std::make_shared<Context>(std::move(std::make_unique<TaskService>(TaskService::Create()))),
      std::move(std::make_unique<IO_Layer>())
  );

  menu.Execute();
  return 0;
}