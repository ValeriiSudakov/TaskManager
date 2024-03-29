//
// Created by valeriisudakov on 01.09.20.
//

#include "InputTask.h"
#include "Factory.h"
#include "InputOutputConsoleLayer.h"

InputTask::InputTask() : State(StatesID::INPUT_TASK){}

InputTask::~InputTask() = default;

StateOperationResult InputTask::Do(const std::shared_ptr<Context> &context, InputOutputLayer& io) {
  auto stateMachine = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_TASK_PARAMS,
                                                        context,
                                                        io);

  stateMachine->Execute();
  return StateOperationResult::SUCCESS;
}