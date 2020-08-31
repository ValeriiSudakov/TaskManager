//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowTodayState.h"
#include "States/BaseState.h"
#include "Factory.h"

ShowTodayState::ShowTodayState() : State(StatesID::ShowToday){ }

ShowTodayState::~ShowTodayState() = default;


StateOperationResult ShowTodayState::Do(const std::shared_ptr<Context>& context) {
  std::string inputSort;
  if (inputSort == "y") {
    context->tasks_ = context->taskService_->GetTodayTasks(true);
  } else if (inputSort == "n") {
    context->tasks_ = context->taskService_->GetTodayTasks(false);
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

std::shared_ptr<State> ShowTodayState::ReadAction() {
  return Factory::CreateState(StatesID::Base);
}
