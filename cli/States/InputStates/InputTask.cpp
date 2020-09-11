//
// Created by valeriisudakov on 01.09.20.
//

#include "InputTask.h"
#include "Factory/Factory.h"

InputTask::InputTask() : State(StatesID::InputTask){}

InputTask::~InputTask() = default;

StateOperationResult InputTask::Do(const std::shared_ptr<Context> &context, const InputOutputLayer &io) {
  auto contextForInput = std::make_shared<Context>(nullptr);
  std::unique_ptr<StateMachine> stateMachine = std::make_unique<FiniteStateMachine>(
                                                std::list<StatesID>{
                                                  StatesID::InputName,
                                                  StatesID::InputLabel,
                                                  StatesID::InputPriority,
                                                  StatesID::InputDate,
                                                  StatesID::Exit
                                                },
                                                contextForInput,
                                                std::move(std::make_unique<InputOutpuConsoleLayer>())
                                              );
  stateMachine->Execute();
  context->buffer_ = contextForInput->buffer_;
  return StateOperationResult::SUCCESS;
}