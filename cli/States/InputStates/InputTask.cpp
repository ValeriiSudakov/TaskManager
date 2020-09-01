//
// Created by valeriisudakov on 01.09.20.
//

#include "InputTask.h"
#include "Factory.h"

InputTask::InputTask() : State(StatesID::InputTask){}

InputTask::~InputTask() = default;

StateOperationResult InputTask::Do(const std::shared_ptr<Context> &context, const IO_LayerInterface &IO) {
  auto stateMachine = Factory::CreateStateMachine(FiniteStateMachinesList::InputTask, context);
  stateMachine.Execute();
  return StateOperationResult::SUCCESS;
}