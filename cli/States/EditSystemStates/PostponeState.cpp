//
// Created by valeriisudakov on 20.08.20.
//

#include "PostponeState.h"
#include "States/BaseState.h"
#include "Factory.h"
PostponeState::PostponeState() : State(StatesID::Postpone){}

PostponeState::~PostponeState() = default;

StateOperationResult PostponeState::Do(const std::shared_ptr<Context>& context) {
  auto postponeMachine = Factory::CreateStateMachine(FiniteStateMachinesList::Postpone, context);
  postponeMachine.Execute();

  auto result = context->taskService_->PostponeTask(context->buffer_.id, context->buffer_.date);
  if (result){
    std::cout<<"Task postponed successfully.\n";
    return StateOperationResult::SUCCESS;
  } else {
    std::cout<<"Postpone failed.\n";
    return StateOperationResult::FAIL;
  }
}

std::shared_ptr<State> PostponeState::ReadAction() {
  return Factory::CreateState(StatesID::Base);
}