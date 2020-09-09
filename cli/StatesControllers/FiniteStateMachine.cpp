//
// Created by valeriisudakov on 27.08.20.
//

#include "FiniteStateMachine.h"
#include "Factory/Factory.h"

void FiniteStateMachine::Execute(){
  auto nextState = states_.begin();
  auto state = Factory::CreateState(*nextState);
  while (state){
    auto result = state->Do(context_, *io_);
    if (result == StateOperationResult::SUCCESS){
      nextState++;
    }
    state = Factory::CreateState(*nextState);
  }
  io_->Output("\n");
}