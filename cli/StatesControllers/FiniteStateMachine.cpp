//
// Created by valeriisudakov on 27.08.20.
//

#include "FiniteStateMachine.h"
#include "Factory/Factory.h"

FiniteStateMachine::FiniteStateMachine(const std::map<StatesID, std::map<StateOperationResult, StatesID>>& stateTransitionTable,
                                       const StatesID& firstState,
                                       const std::shared_ptr<Context>& context,
                                       std::unique_ptr<IO_LayerInterface> io)
                                       :
                                       StateMachine(firstState, context, std::move(io)) ,
                                       stateTransitionTable_(stateTransitionTable) {}

FiniteStateMachine::~FiniteStateMachine() = default;


void FiniteStateMachine::Execute(){
  auto state = Factory::CreateState(firstState_);
  while (state){
    auto result = state->Do(context_, *io_);
    auto nextState = stateTransitionTable_[state->GetStateID()];
    auto nextStateID = nextState.find(result);

    if (nextStateID != nextState.end()){
      state = Factory::CreateState(nextStateID->second);
    } else {
      std::string error {"Unexpected behavior.\n" };
      io_->Output(error);
      break;
    }
  }
  std::cout<<"______________________________________________________\n";
}