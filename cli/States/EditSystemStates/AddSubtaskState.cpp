//
// Created by valeriisudakov on 20.08.20.
//

#include "AddSubtaskState.h"
#include "Factory/Factory.h"
#include "InputOutputConsoleLayer.h"

AddSubtaskState::AddSubtaskState() : State(StatesID::ADD_SUBTASK){ }

AddSubtaskState::~AddSubtaskState() = default;

StateOperationResult AddSubtaskState::Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) {
  auto addTaskMachine = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_SUBTASK_PARAMS,
                                                           context,
                                                           io);
  addTaskMachine->Execute();
  auto task = TaskServiceDTO::Create(context->buffer_.name, context->buffer_.label,
                         context->buffer_.priority, context->buffer_.date);
  if (!task.has_value()){
    return StateOperationResult::FAIL;
  }
  auto result = context->taskService_.AddSubtask(context->buffer_.id, task.value());

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

