//
// Created by valeriisudakov on 20.08.20.
//

#include "CompleteState.h"
#include "Factory/Factory.h"
#include "InputOutputConsoleLayer.h"

CompleteState::CompleteState() : State(StatesID::COMPLETE) {}

CompleteState::~CompleteState() = default;

StateOperationResult CompleteState::Do(const std::shared_ptr<Context>& context, const InputOutputLayer& io) {
  auto inputIDMachine = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_ID,
                                                           context,
                                                           std::move(std::make_unique<InputOutputConsoleLayer>()));

  inputIDMachine->Execute();

  auto result = context->taskService_->SetTaskComplete(context->buffer_.id);
  if (result){
    std::string success { "Task was completed.\n" };
    io.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Error.\n" };
    io.Output(fail);
    return StateOperationResult::FAIL;
  }
}
