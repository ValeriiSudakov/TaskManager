//
// Created by valeriisudakov on 05.10.20.
//

#include "SaveState.h"
#include "Factory/Factory.h"
#include "InputOutputConsoleLayer.h"

SaveState::SaveState() : State(StatesID::SAVE){}

SaveState::~SaveState() = default;

StateOperationResult SaveState::Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) {
  auto result = context->taskService_.Save();
  if (result){
    std::string success { "Tasks were saved.\n" };
    io.Output(success);
  } else {
    std::string fail { "Smth wrong...\n" };
    io.Output(fail);
  }
  return StateOperationResult::SUCCESS;
}