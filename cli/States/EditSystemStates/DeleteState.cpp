//
// Created by valeriisudakov on 20.08.20.
//

#include "DeleteState.h"
#include "Factory/Factory.h"
#include "InputOutputConsoleLayer.h"

DeleteState::DeleteState() : State(StatesID::DELETE){}

DeleteState::~DeleteState() = default;

StateOperationResult DeleteState::Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) {
  auto inputIDMachine = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_ID,
                                                           context,
                                                           io);
  inputIDMachine->Execute();

  auto result = context->taskService_.RemoveTask(context->buffer_.id);
  if (result){
    std::string success { "Task was removed.\n" };
   io.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Task was not found.\n" };
   io.Output(fail);
    return StateOperationResult::FAIL;
  }
}

