//
// Created by valeriisudakov on 27.08.20.
//

#include "FiniteStateMachine.h"
#include "Factory.h"

FiniteStateMachine::FiniteStateMachine(const std::map<StatesID, std::map<StateOperationResult, StatesID>>& stateTransitionTable,
                                       StatesID firstState,
                                       const std::shared_ptr<Context>& context) :
    stateTransitionTable_(stateTransitionTable), firstState_(firstState), context_(context){}

FiniteStateMachine::~FiniteStateMachine() = default;


void FiniteStateMachine::Execute(){
  auto state = Factory::CreateState(firstState_);
  while (state){
    if (state->GetStateID() == StatesID::Base){
      state = state->ReadAction();
    } else {
      auto result = state->Do(context_);
      auto nextState = stateTransitionTable_[state->GetStateID()];
      auto nextStateID = nextState.find(result);
      if (nextStateID != nextState.end()){
        state = Factory::CreateState(nextStateID->second);
      } else {
        state = Factory::CreateState(StatesID::Base);
      }
    }
    std::cout<<"______________________________________________________\n";
  }
}