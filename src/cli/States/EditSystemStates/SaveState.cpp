//
// Created by valeriisudakov on 05.10.20.
//

#include "SaveState.h"
#include "Factory/Factory.h"
#include "InputOutputConsoleLayer.h"

SaveState::SaveState() : State(StatesID::SAVE){}

SaveState::~SaveState() = default;

StateOperationResult SaveState::Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) {
  auto inputFileNameMachine = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_FILE_NAME,
                                                                 context,
                                                                 io);
  inputFileNameMachine->Execute();
  auto result = context->taskService_.Save(context->buffer_.fileName);
  if (result){
    std::string success { "Tasks were saved.\n" };
    io.Output(success);
  } else {
    std::string fail { "Smth wrong...\n" };
    io.Output(fail);
  }
  return StateOperationResult::SUCCESS;
}