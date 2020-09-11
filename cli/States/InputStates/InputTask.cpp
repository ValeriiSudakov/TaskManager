//
// Created by valeriisudakov on 01.09.20.
//

#include "InputTask.h"
#include "Factory/Factory.h"

InputTask::InputTask() : State(StatesID::INPUT_TASK){}

InputTask::~InputTask() = default;

StateOperationResult InputTask::Do(const std::shared_ptr<Context> &context, const InputOutputLayer &io) {
  auto contextForInput = std::make_shared<Context>(nullptr);
  std::unique_ptr<StateMachine> stateMachine = std::make_unique<FiniteStateMachine>(
                                                std::list<StatesID>{
                                                  StatesID::INPUT_NAME,
                                                  StatesID::INPUT_LABEL,
                                                  StatesID::INPUT_PRIORITY,
                                                  StatesID::INPUT_DATE,
                                                  StatesID::EXIT
                                                },
                                                contextForInput,
                                                std::move(std::make_unique<InputOutpuConsoleLayer>())
                                              );
  stateMachine->Execute();
  context->buffer_ = contextForInput->buffer_;
  return StateOperationResult::SUCCESS;
}