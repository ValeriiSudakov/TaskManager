//
// Created by valeriisudakov on 04.09.20.
//

#include "StateMachineMenu.h"
#include "Factory/Factory.h"

StateMachineMenu::StateMachineMenu(const StatesID& firstState,
                                          const std::shared_ptr<Context>& context,
                                          std::unique_ptr<IO_LayerInterface> io)
                                          :
                                          StateMachine(firstState, context, std::move(io)) {}

StateMachineMenu::~StateMachineMenu() = default;


void StateMachineMenu::Execute(){
  auto state = Factory::CreateState(firstState_);
  while (state){
    state->Do(context_, *io_);
    state = state->ReadAction();
    std::cout<<"______________________________________________________\n";
  }
}