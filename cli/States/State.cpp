//
// Created by valeriisudakov on 18.08.20.
//

#include "State.h"

State::~State() = default;

void State::PrintState(){
  std::cout<<stateName_<<std::endl;
}

void State::PrintNextStates(){}

std::shared_ptr<State> State::ReadAction() {  }