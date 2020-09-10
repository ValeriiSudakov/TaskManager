//
// Created by valeriisudakov on 04.09.20.
//

#include "StateMachineMenu.h"
#include "Factory/Factory.h"

void StateMachineMenu::Execute(){
  auto state = Factory::CreateState(menuID_);
  while (state){
    auto result = state->Do(context_, *io_);
    if ( result == StateOperationResult::TASKS_LIST_EMPTY){
      state = Factory::CreateState(StatesID::BaseMenu);
    }
    state = state->ReadAction();
  }
}