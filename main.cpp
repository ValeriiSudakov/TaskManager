#include "StatesControllers/StatesController.h"
#include "States/EditSystemStates/AddTaskState.h"


int main(){

  StatesController states_controller;
  states_controller.ExecuteProgram();
  std::cout<<"end.\n";
  return 0;
}
