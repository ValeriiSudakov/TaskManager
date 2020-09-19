
#include "StatesControllers/StateMachineMenu.h"
#include "InputOutputConsoleLayer.h"
#include "States/StatesID.h"

#include "Factory/Factory.h"

int main(){
  auto io = std::make_shared<InputOutputConsoleLayer>();
  std::unique_ptr<TaskService> service = std::make_unique<TaskServiceClass>(TaskServiceClass::Create());
  auto menu = Factory::CreateMenuStateMachine(StatesID::BASE_MENU,
                                               std::make_shared<Context>(*service),*io );
  menu->Execute();
  return 0;
}