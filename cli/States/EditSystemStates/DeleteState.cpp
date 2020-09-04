//
// Created by valeriisudakov on 20.08.20.
//

#include "DeleteState.h"
#include "States/BaseState.h"
#include "Factory/Factory.h"
DeleteState::DeleteState() : State(StatesID::Delete){}

DeleteState::~DeleteState() = default;

StateOperationResult DeleteState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) {
  auto inputIDMachine = Factory::CreateStateMachine(FiniteStateMachinesList::ChooseID, context);
  inputIDMachine->Execute();

  auto result = context->taskService_->RemoveTask(context->buffer_.id);
  if (result){
    std::string success { "Task was removed.\n" };
    IO.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Task was not found.\n" };
    IO.Output(fail);
    return StateOperationResult::FAIL;
  }
}

std::shared_ptr<State> DeleteState::ReadAction() {
  return Factory::CreateState(StatesID::Base);
}
