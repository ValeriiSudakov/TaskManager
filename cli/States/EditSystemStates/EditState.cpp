//
// Created by valeriisudakov on 10.09.20.
//

#include "EditState.h"
#include "StatesControllers/FiniteStateMachine.h"
#include "InputOutpuConsoleLayer.h"
#include "Factory/Factory.h"

StateOperationResult EditState::Do(const std::shared_ptr<Context> &context, const InputOutputLayer &io) {
  std::unique_ptr<StateMachine> editMachine = std::make_unique<FiniteStateMachine>(
      std::list<StatesID>{
          editStateID_,
          StatesID::Exit
      },
      context,
      std::move(std::make_unique<InputOutpuConsoleLayer>())
  );
  editMachine->Execute();
  return StateOperationResult::SUCCESS;
}

std::shared_ptr<State> EditState::ReadAction() {
  return std::move(Factory::CreateState(StatesID::BaseMenu));
}