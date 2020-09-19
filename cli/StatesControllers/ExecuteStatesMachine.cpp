//
// Created by valeriisudakov on 27.08.20.
//

#include "ExecuteStatesMachine.h"
#include "Factory/Factory.h"

void ExecuteStatesMachine::Execute(){
  auto statesIterator = states_.begin();
  StatesID nextState = *statesIterator;
  auto state = Factory::CreateState(*statesIterator);
  while (state){
    auto result = state->Do(context_, io_);
    if (StateOperationResult::SUCCESS == result){
      nextState = *(++statesIterator);
    } else if (StateOperationResult::TASKS_LIST_EMPTY == result){
      nextState = StatesID::EXIT;
    }
    state = Factory::CreateState(nextState);
  }
}