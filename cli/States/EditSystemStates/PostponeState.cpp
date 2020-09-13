//
// Created by valeriisudakov on 20.08.20.
//

#include "PostponeState.h"
#include "Factory/Factory.h"
#include "InputOutpuConsoleLayer.h"
PostponeState::PostponeState() : State(StatesID::POSTPONE){}

PostponeState::~PostponeState() = default;

StateOperationResult PostponeState::Do(const std::shared_ptr<Context>& context, const InputOutputLayer& io) {
  auto postponeMachine = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::POSTPONE,
                                                            context,
                                                            std::move(std::make_unique<InputOutpuConsoleLayer>()));

  postponeMachine->Execute();

  auto result = context->taskService_->PostponeTask(context->buffer_.id, context->buffer_.date);
  if (result){
    std::string success { "Task postponed successfully.\n" };
    io.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Postpone failed.\n" };
    io.Output(fail);
    return StateOperationResult::FAIL;
  }
}
