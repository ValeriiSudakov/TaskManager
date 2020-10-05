//
// Created by valeriisudakov on 05.10.20.
//

#include "LoadState.h"
#include "Factory/Factory.h"
#include "InputOutputConsoleLayer.h"

LoadState::LoadState() : State(StatesID::LOAD){}

LoadState::~LoadState() = default;

StateOperationResult LoadState::Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) {
  auto result = context->taskService_.Load();
  if (result){
    std::string success { "Tasks were loaded.\n" };
    io.Output(success);
  } else {
    std::string fail { "Smth wrong...\n" };
    io.Output(fail);
  }
  return StateOperationResult::SUCCESS;
}