//
// Created by valeriisudakov on 19.08.20.
//

#include "StatesController.h"
#include "States/BaseState.h"


StatesController::StatesController(){
  state_ = std::move(std::make_shared<BaseState>());
  context_ = std::make_unique<Context>();
}

StatesController::~StatesController() = default;

void StatesController::ExecuteProgram(){
  while (state_){
    std::cout<<"____________________________\n";
    state_->Do(*context_);
    state_ = std::move(state_->ReadAction());

  }
}