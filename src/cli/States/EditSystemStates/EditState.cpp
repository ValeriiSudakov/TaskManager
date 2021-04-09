//
// Created by valeriisudakov on 10.09.20.
//

#include "EditState.h"
#include "InputOutputConsoleLayer.h"
#include "Factory.h"

StateOperationResult EditState::Do(const std::shared_ptr<Context> &context, InputOutputLayer& io) {
  auto editMachine = Factory::CreateAfterMenuState(   editStateID_,
                                                      context,
                                                      io);
  editMachine->Execute();
  return StateOperationResult::SUCCESS;
}

std::shared_ptr<State> EditState::ReadAction(InputOutputLayer& io) {
  return Factory::CreateState(StatesID::BASE_MENU);
}