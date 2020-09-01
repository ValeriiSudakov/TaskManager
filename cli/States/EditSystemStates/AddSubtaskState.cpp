//
// Created by valeriisudakov on 20.08.20.
//

#include "AddSubtaskState.h"
#include "States/BaseState.h"
#include "Factory.h"

AddSubtaskState::AddSubtaskState() : State(StatesID::AddSubtask){ }

AddSubtaskState::~AddSubtaskState() = default;

StateOperationResult AddSubtaskState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) {
  auto addTaskMachine = Factory::CreateStateMachine(FiniteStateMachinesList::AddSubtask, context);
  addTaskMachine.Execute();

  auto result = context->taskService_->AddSubtask(context->buffer_.id,
                                                 TaskDTO::Create(context->buffer_.name, context->buffer_.label,
                                                                 context->buffer_.priority, context->buffer_.date));

  if (result.success_){
    std::string success {"Subtask was added.\n"} ;
    IO.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Failed.\n" };
    IO.Output(fail);
    return StateOperationResult::FAIL;
  }
}

std::shared_ptr<State> AddSubtaskState::ReadAction() {
  return Factory::CreateState(StatesID::Base);
}
