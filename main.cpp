#include "StatesControllers/FiniteStateMachine.h"

int main(){

  FiniteStateMachine FSM(std::map<StatesID, std::map<StateOperationResult, StatesID>>{},
                         StatesID::Base,
                         std::make_shared<Context>());
  FSM.Execute();
  return 0;
}
