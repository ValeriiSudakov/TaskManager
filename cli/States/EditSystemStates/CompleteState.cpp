//
// Created by valeriisudakov on 20.08.20.
//

#include "CompleteState.h"
#include "States/BaseState.h"
#include "Factory/Factory.h"
CompleteState::CompleteState() : State(StatesID::Complete) {}

CompleteState::~CompleteState() = default;

StateOperationResult CompleteState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) {
  auto completeStateMachine = Factory::CreateStateMachine(FiniteStateMachinesList::ChooseID, context);
  completeStateMachine->Execute();

  auto result = context->taskService_->SetTaskComplete(context->buffer_.id);
  if (result){
    std::string success { "Task was completed.\n" };
    IO.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Error.\n" };
    IO.Output(fail);
    return StateOperationResult::FAIL;
  }
}

std::shared_ptr<State> CompleteState::ReadAction() {
  return Factory::CreateState(StatesID::Base);
}