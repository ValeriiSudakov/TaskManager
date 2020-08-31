//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowByNameState.h"
#include "States/BaseState.h"
#include "Factory.h"
ShowByNameState::ShowByNameState() : State (StatesID::ShowByName) {}

ShowByNameState::~ShowByNameState() = default;

void Print(){
  std::cout<<"Tasks list will be updated. Sort tasks by priority? [y/n]: ";
}

std::string Read(){
  std::string str;
  std::getline(std::cin, str);
  return str;
}

StateOperationResult ShowByNameState::Do(const std::shared_ptr<Context>& context) {
  auto showByNameMachine = Factory::CreateStateMachine(FiniteStateMachinesList::ShowByName, context);
  showByNameMachine.Execute();

  Print();
  std::string inputSort = Read();

  if (inputSort == "y") {
    context->tasks_ = context->taskService_->GetTasksByName(context->buffer_.name, true);
  } else if (inputSort == "n") {
    context->tasks_ = context->taskService_->GetTasksByName(context->buffer_.name, false);
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

std::shared_ptr<State> ShowByNameState::ReadAction() {
  return Factory::CreateState(StatesID::Base);
}