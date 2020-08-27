//
// Created by valeriisudakov on 27.08.20.
//

#include "FiniteStateMachine.h"
#include "Factory.h"

FiniteStateMachine::FiniteStateMachine(const std::vector<InputStatesList>& nextStates, const std::shared_ptr<Context>& context) :
  nextStates_(nextStates), context_(context){}

FiniteStateMachine::~FiniteStateMachine() = default;

void FiniteStateMachine::Execute(){
  short int state = 0;
  while (state < nextStates_.size()){
    auto currentState = Factory::CreateInputState(nextStates_[state]);
    auto result = currentState->Do(context_);
    if (result){
      state++;
    }
  }
}