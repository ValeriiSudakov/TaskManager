//
// Created by valeriisudakov on 20.08.20.
//

#include "CompleteState.h"
#include "States/BaseState.h"
#include "Factory.h"
CompleteState::CompleteState() : State(StatesID::Complete) {}

CompleteState::~CompleteState() = default;

StateOperationResult CompleteState::Do(const std::shared_ptr<Context>& context) {
  auto completeStateMachine = Factory::CreateStateMachine(FiniteStateMachinesList::InputID, context);
  completeStateMachine.Execute();

  auto result = context->taskService_->SetTaskComplete(context->buffer_.id);
  if (result){
    std::cout<<"Task was completed.\n";
    return StateOperationResult::SUCCESS;
  } else {
    std::cout<<"Error.\n";
    return StateOperationResult::FAIL;
  }
}

std::shared_ptr<State> CompleteState::ReadAction() {
  return Factory::CreateState(StatesID::Base);
}