#include "StatesControllers/FiniteStateMachine.h"
#include "IO_Layer.h"

int main(){

  FiniteStateMachine FSM(std::map<StatesID, std::map<StateOperationResult, StatesID>>{},
                         StatesID::Base,
                         std::make_shared<Context>(),
                         std::move(std::make_unique<IO_Layer>()));
  FSM.Execute();
  return 0;
}
