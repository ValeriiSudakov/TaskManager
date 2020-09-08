//
// Created by valeriisudakov on 20.08.20.
//

#include "PostponeState.h"
#include "States/Menu.h"
#include "Factory/Factory.h"
PostponeState::PostponeState() : State(StatesID::Postpone){}

PostponeState::~PostponeState() = default;

StateOperationResult PostponeState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) {
  auto postponeMachine = Factory::CreateStateMachine(FiniteStateMachinesList::Postpone, context);
  postponeMachine->Execute();
  auto result = context->taskService_->PostponeTask(context->buffer_.id, context->buffer_.date);
  if (result){
    std::string success { "Task postponed successfully.\n" };
    IO.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Postpone failed.\n" };
    IO.Output(fail);
    return StateOperationResult::FAIL;
  }
}

std::shared_ptr<State> PostponeState::ReadAction() {
  return Factory::CreateState(StatesID::Menu);
}