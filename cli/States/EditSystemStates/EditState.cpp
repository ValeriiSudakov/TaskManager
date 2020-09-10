//
// Created by valeriisudakov on 10.09.20.
//

#include "EditState.h"
#include "StatesControllers/FiniteStateMachine.h"
#include "IO_Layer.h"
#include "Factory/Factory.h"

StateOperationResult EditState::Do(const std::shared_ptr<Context> &context, const IO_LayerInterface &IO) {
  std::unique_ptr<StateMachine> editMachine = std::make_unique<FiniteStateMachine>(
      std::list<StatesID>{
          editStateID_,
          StatesID::Exit
      },
      context,
      std::move(std::make_unique<IO_Layer>())
  );
  editMachine->Execute();
  return StateOperationResult::SUCCESS;
}

std::shared_ptr<State> EditState::ReadAction() {
  return std::move(Factory::CreateState(StatesID::BaseMenu));
}