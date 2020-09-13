//
// Created by valeriisudakov on 09.09.20.
//
#include "Factory/Factory.h"
#include "ShowState.h"
#include "InputOutputConsoleLayer.h"

StateOperationResult ShowState::Do(const std::shared_ptr<Context> &context, const InputOutputLayer &IO) {
  auto showMachine = Factory::CreateAfterMenuState(   showStateID_,
                                                      context,
                                                      std::move(std::make_unique<InputOutputConsoleLayer>()));
  showMachine->Execute();

  if (context->tasks_.empty()){
    return StateOperationResult::TASKS_LIST_EMPTY;
  }

  return StateOperationResult::SUCCESS;
}

std::shared_ptr<State> ShowState::ReadAction() {
  return Factory::CreateState(StatesID::CONTINUE_MENU);
}