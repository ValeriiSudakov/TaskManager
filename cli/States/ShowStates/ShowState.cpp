//
// Created by valeriisudakov on 09.09.20.
//

#include "ShowState.h"
#include "StatesControllers/StateMachineMenu.h"
#include "StatesControllers/FiniteStateMachine.h"
#include "IO_Layer.h"
StateOperationResult ShowState::Do(const std::shared_ptr<Context> &context, const IO_LayerInterface &IO) {

  std::unique_ptr<StateMachine> showMachine = std::make_unique<FiniteStateMachine>(
      std::list<StatesID>{
          showStateID_,
          StatesID::Exit
      },
      context,
      std::move(std::make_unique<IO_Layer>())
  );
  showMachine->Execute();

  std::unique_ptr<StateMachineMenu> menu = std::make_unique<StateMachineMenu> (
      StatesID::ContinueMenu,
      context,
      std::move(std::make_unique<IO_Layer>())
  );

  menu->Execute();
  return StateOperationResult::SUCCESS;
}