//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowByNameState.h"
#include "States/BaseState.h"
#include "Factory.h"
ShowByNameState::ShowByNameState() : State(StatesID::ShowByName){}

ShowByNameState::~ShowByNameState() = default;



StateOperationResult ShowByNameState::Do(const std::shared_ptr<Context>& context) {
  auto showByNameMachine = Factory::CreateStateMachine(FiniteStateMachinesList::ShowByName, context);
  showByNameMachine.Execute();

  std::string inputSort;
  if (inputSort == "y") {
    context->tasks_ = context->taskService_->GetTasksByName(context->buffer_.name, true);
  } else if (inputSort == "n") {
    context->tasks_ = context->taskService_->GetTasksByName(context->buffer_.name, false);
  } else {
    std::cout<<"Incorrect input.\n";
    return StateOperationResult::INCORRECT_INPUT;
  }
  int taskNumber = 0;
  for (const auto& task : context->tasks_){
    std::cout<<taskNumber++<<": "<<task.GetName()<<std::endl;
  }
  return StateOperationResult::SUCCESS;
}

std::shared_ptr<State> ShowByNameState::ReadAction() {
  return Factory::CreateState(StatesID::Base);
}