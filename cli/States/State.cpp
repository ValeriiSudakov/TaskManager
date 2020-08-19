//
// Created by valeriisudakov on 18.08.20.
//

#include "State.h"

State::~State() = default;

void State::PrintState(){
  std::cout<<stateName_<<std::endl;
}

void State::SetContext(std::shared_ptr<Context> context){
  context_ = context;
}
