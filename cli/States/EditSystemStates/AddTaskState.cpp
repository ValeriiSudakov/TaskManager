//
// Created by valeriisudakov on 18.08.20.
//

#include "AddTaskState.h"
#include "Factory/Factory.h"
#include "InputOutputConsoleLayer.h"

AddTaskState::AddTaskState() : State(StatesID::ADD_TASK){}

AddTaskState::~AddTaskState() = default;

StateOperationResult AddTaskState::Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) {
  auto addTaskMachine = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_TASK_PARAMS,
                                                           context,
                                                           io);
  addTaskMachine->Execute();

//  auto result = context->taskService_->AddTask(TaskDTO::Create(context->buffer_.name, context->buffer_.label,
//                                                context->buffer_.priority, context->buffer_.date));

//  if (result.success_){
//    std::string success {"Task was added.\n"};
//   io.Output(success);
    return StateOperationResult::SUCCESS;
//  } else {
//    std::string fail { "Failed.\n" };
//    return StateOperationResult::FAIL;
//  }
}
