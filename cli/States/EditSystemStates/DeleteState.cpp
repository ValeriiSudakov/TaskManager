//
// Created by valeriisudakov on 20.08.20.
//

#include "DeleteState.h"
#include "States/BaseState.h"
#include "Factory.h"
DeleteState::DeleteState(){
  stateID_ = StatesID::Delete;
}

DeleteState::~DeleteState() = default;

StateOperationResult DeleteState::Do(const std::shared_ptr<Context>& context) {
  auto inputIDMachine = Factory::CreateStateMachine(FiniteStateMachinesList::InputID, context);
  inputIDMachine.Execute();

  auto result = context->taskService_->RemoveTask(context->buffer_.id);
  if (result){
    std::cout<<"Task was removed.\n";
    return StateOperationResult::SUCCESS;
  } else {
    std::cout<<"Task was not found.\n";
    return StateOperationResult::FAIL;
  }
}

std::shared_ptr<State> DeleteState::ReadAction() {
  return Factory::CreateState(StatesID::Base);
}
