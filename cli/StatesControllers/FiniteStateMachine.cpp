//
// Created by valeriisudakov on 27.08.20.
//

#include "FiniteStateMachine.h"
#include "Factory/Factory.h"

void FiniteStateMachine::Execute(){
  auto statesIterator = states_.begin();
  StatesID nextState = *statesIterator;
  auto state = Factory::CreateState(*statesIterator);
  while (state){
    auto result = state->Do(context_, *io_);
    if (result == StateOperationResult::SUCCESS){
      nextState = *(++statesIterator);
    } else if (result == StateOperationResult::TASKS_LIST_EMPTY){
      nextState = StatesID::Exit;
    }
    state = Factory::CreateState(nextState);
  }
}