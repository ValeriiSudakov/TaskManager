//
// Created by valeriisudakov on 09.09.20.
//
#include "Factory/Factory.h"
#include "ShowState.h"
#include "StatesControllers/StateMachineMenu.h"
#include "StatesControllers/FiniteStateMachine.h"
#include "InputOutpuConsoleLayer.h"
StateOperationResult ShowState::Do(const std::shared_ptr<Context> &context, const InputOutputLayer &IO) {

  std::unique_ptr<StateMachine> showMachine = std::make_unique<FiniteStateMachine>(
      std::list<StatesID>{
          showStateID_,
          StatesID::EXIT
      },
      context,
      std::move(std::make_unique<InputOutpuConsoleLayer>())
  );
  showMachine->Execute();

  if (context->tasks_.empty()){
    return StateOperationResult::TASKS_LIST_EMPTY;
  }

  return StateOperationResult::SUCCESS;
}

std::shared_ptr<State> ShowState::ReadAction() {
  return Factory::CreateState(StatesID::CONTINUE_MENU);
}