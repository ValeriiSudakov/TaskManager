//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowByLabelState.h"
#include "States/BaseState.h"
#include "Factory.h"

ShowByLabelState::ShowByLabelState() : State(StatesID::ShowByLabel){}

ShowByLabelState::~ShowByLabelState() = default;

StateOperationResult ShowByLabelState::Do(const std::shared_ptr<Context>& context) {
  auto showByLabelMachine = Factory::CreateStateMachine(FiniteStateMachinesList::ShowByLabel, context);
  showByLabelMachine.Execute();

  std::cout<<"Tasks list will be updated. Sort tasks by priority? [y/n]: ";
  std::string inputSort;
  std::getline(std::cin, inputSort);
  if (inputSort == "y") {
    context->tasks_ = context->taskService_->GetTasksByLabel(context->buffer_.label, true);
  } else if (inputSort == "n") {
    context->tasks_ = context->taskService_->GetTasksByLabel(context->buffer_.label, false);
  } else {
    std::cout<<"Incorrect input.\n";
    return StateOperationResult::INCORRECT_INPUT;
  }
  if (context->tasks_.empty()){
    std::cout<<"Tasks were not found.\n";
    return StateOperationResult::TASKS_LIST_EMPTY;
  }
  int taskNumber = 0;
  for (const auto& task : context->tasks_){
    std::cout<<taskNumber++<<": "<<task.GetName()<<std::endl;
  }
  return StateOperationResult::SUCCESS;
}

std::shared_ptr<State> ShowByLabelState::ReadAction() {
  return Factory::CreateState(StatesID::Base);
}
