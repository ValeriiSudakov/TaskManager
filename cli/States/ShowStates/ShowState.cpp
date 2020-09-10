//
// Created by valeriisudakov on 09.09.20.
//
#include "Factory/Factory.h"
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

  if (context->tasks_.empty()){
    return StateOperationResult::TASKS_LIST_EMPTY;
  }

  return StateOperationResult::SUCCESS;
}

std::shared_ptr<State> ShowState::ReadAction() {
  return std::move(Factory::CreateState(StatesID::ContinueMenu));
}