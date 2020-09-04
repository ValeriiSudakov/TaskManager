//
// Created by valeriisudakov on 01.09.20.
//

#include "InputTask.h"
#include "Factory/Factory.h"

InputTask::InputTask() : State(StatesID::InputTask){}

InputTask::~InputTask() = default;

StateOperationResult InputTask::Do(const std::shared_ptr<Context> &context, const IO_LayerInterface &IO) {
  auto contextForInput = std::make_shared<Context>(nullptr);
  auto stateMachine = Factory::CreateStateMachine(FiniteStateMachinesList::InputTask, contextForInput);
  stateMachine->Execute();
  context->buffer_ = contextForInput->buffer_;
  return StateOperationResult::SUCCESS;
}