#include "StatesController.h"
#include "cli/States/AddTaskState.h"


int main(){

  StatesController states_controller;
  states_controller.ExecuteProgram();
  std::cout<<"end.\n";
  return 0;
}
