//
// Created by valeriisudakov on 27.08.20.
//

#include "FiniteStateMachine.h"
#include "Factory.h"

FiniteStateMachine::FiniteStateMachine(const std::map<StatesID, std::map<StateOperationResult, StatesID>>& stateTransitionTable,
                                       const StatesID& firstState,
                                       const std::shared_ptr<Context>& context,
                                       std::unique_ptr<IO_LayerInterface> io) :
    stateTransitionTable_(stateTransitionTable), firstState_(firstState), context_(context), io_(std::move(io)){}

FiniteStateMachine::~FiniteStateMachine() = default;


void FiniteStateMachine::Execute(){
  auto state = Factory::CreateState(firstState_);
  while (state){
    if (state->GetStateID() == StatesID::Base){
      state = state->ReadAction();
    } else {
      auto result = state->Do(context_, *io_);
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