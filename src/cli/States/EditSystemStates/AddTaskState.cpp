//
// Created by valeriisudakov on 18.08.20.
//

#include "AddTaskState.h"
#include "Factory.h"
#include "InputOutputConsoleLayer.h"
#include "TaskServiceDTO.h"

AddTaskState::AddTaskState() : State(StatesID::ADD_TASK){}

AddTaskState::~AddTaskState() = default;

StateOperationResult AddTaskState::Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) {
  auto addTaskMachine = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_TASK_PARAMS,
                                                           context,
                                                           io);
  addTaskMachine->Execute();


  auto task = TaskServiceDTO::Create(context->buffer_.name, context->buffer_.label,
                                     context->buffer_.priority, context->buffer_.date);
  if (!task.has_value()){
    return StateOperationResult::FAIL;
  }
  auto result = context->taskService_.AddTask(task.value());

  if (result.success_){
    std::string success {"Task was added.\n"};
    io.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Failed.\n" };
    io.Output(fail);
    return StateOperationResult::FAIL;
  }
}
