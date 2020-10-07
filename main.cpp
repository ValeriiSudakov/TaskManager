
#include "StatesControllers/StateMachineMenu.h"
#include "InputOutputConsoleLayer.h"
#include "States/StatesID.h"
#include "Memory_Model/RepositoriesFactory/TaskRepositoryFactory.h"
#include "Memory_Model/Storage/TaskRepositoryController.h"
#include "Factory/Factory.h"

int main(){
  std::unique_ptr<RepositoriesFactory> factory = std::make_unique<TaskRepositoryFactory>();
  std::unique_ptr<RepositoryController> controller = std::make_unique<TaskRepositoryController>(std::move(std::move(factory)));
  std::unique_ptr<TaskService> service = std::make_unique<TaskServiceClass>(std::move(controller));

  auto io = std::make_shared<InputOutputConsoleLayer>();

  auto menu = Factory::CreateMenuStateMachine(StatesID::BASE_MENU,
                                               std::make_shared<Context>(*service),*io );

  menu->Execute();
  return 0;
}