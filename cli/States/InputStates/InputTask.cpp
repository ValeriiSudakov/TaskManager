//
// Created by valeriisudakov on 01.09.20.
//

#include "InputTask.h"
#include "Factory/Factory.h"
#include "InputOutpuConsoleLayer.h"

InputTask::InputTask() : State(StatesID::INPUT_TASK){}

InputTask::~InputTask() = default;

StateOperationResult InputTask::Do(const std::shared_ptr<Context> &context, const InputOutputLayer &io) {
  auto stateMachine = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_TASK_PARAMS,
                                                        context,
                                                        std::move(std::make_unique<InputOutpuConsoleLayer>()));

  stateMachine->Execute();
  return StateOperationResult::SUCCESS;
}