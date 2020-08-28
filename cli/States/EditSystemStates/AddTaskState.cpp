//
// Created by valeriisudakov on 18.08.20.
//

#include "AddTaskState.h"
#include "States/BaseState.h"
#include "Factory.h"
#include "StatesControllers/FiniteStateMachinesList.h"

AddTaskState::AddTaskState() {
  stateID_ = StatesID::AddTask;
}

AddTaskState::~AddTaskState() = default;

StateOperationResult AddTaskState::Do(const std::shared_ptr<Context>& context) {
  auto addTaskMachine = Factory::CreateStateMachine(FiniteStateMachinesList::AddTask, context);
  addTaskMachine.Execute();

  auto result = context->taskService_->AddTask(TaskDTO::Create(context->buffer_.name, context->buffer_.label,
                                                context->buffer_.priority, context->buffer_.date));

  if (result.success_){
    std::cout<<"Task was added.\n";
    return StateOperationResult::SUCCESS;
  } else {
    std::cout<<"Failed.\n";
    return StateOperationResult::FAIL;
  }
}

std::shared_ptr<State> AddTaskState::ReadAction() {
  return Factory::CreateState(StatesID::Base);
}