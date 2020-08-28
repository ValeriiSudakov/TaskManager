//
// Created by valeriisudakov on 19.08.20.
//

#include "StatesController.h"
#include "States/BaseState.h"
#include "Factory.h"
#include "States/StatesID.h"

StatesController::StatesController(){
  state_ = std::move(Factory::CreateState(StatesID::Base));
  context_ = std::make_shared<Context>();
}

StatesController::~StatesController() = default;

void StatesController::ExecuteProgram(){
  while (state_){
    std::cout<<"____________________________\n";
    state_->Do(context_);
    state_ = std::move(state_->ReadAction());
  }
}