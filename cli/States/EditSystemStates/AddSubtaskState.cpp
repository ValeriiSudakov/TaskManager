//
// Created by valeriisudakov on 20.08.20.
//

#include "AddSubtaskState.h"
#include "Factory/Factory.h"
#include "InputOutpuConsoleLayer.h"

AddSubtaskState::AddSubtaskState() : State(StatesID::ADD_SUBTASK){ }

AddSubtaskState::~AddSubtaskState() = default;

StateOperationResult AddSubtaskState::Do(const std::shared_ptr<Context>& context, const InputOutputLayer& io) {
  auto addTaskMachine = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_SUBTASK_PARAMS,
                                                           context,
                                                           std::move(std::make_unique<InputOutpuConsoleLayer>()));
  addTaskMachine->Execute();
  auto result = context->taskService_->AddSubtask(context->buffer_.id,
                                                 TaskDTO::Create(context->buffer_.name, context->buffer_.label,
                                                                 context->buffer_.priority, context->buffer_.date));

  if (result.success_){
    std::string success {"Subtask was added.\n"} ;
    io.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Failed.\n" };
    io.Output(fail);
    return StateOperationResult::FAIL;
  }
}

