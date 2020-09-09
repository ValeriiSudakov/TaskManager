//
// Created by valeriisudakov on 04.09.20.
//

#include "StateMachineMenu.h"
#include "Factory/Factory.h"

void StateMachineMenu::Execute(){
  auto state = Factory::CreateState(menuID_);
  while (state){
    state->Do(context_, *io_);
    state = state->ReadAction();
  }
  io_->Output("\n");
}