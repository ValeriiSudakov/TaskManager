//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowTodayState.h"
#include "States/BaseState.h"
#include "Factory.h"

ShowTodayState::ShowTodayState(){
  stateName_ = "show today";
}

ShowTodayState::~ShowTodayState() = default;

void ShowTodayState::Do(const std::shared_ptr<Context>& context) {
  std::cout<<"Sort tasks by priority? [y/n]: ";
  std::string inputSort;
  std::getline(std::cin, inputSort);
  if (inputSort == "y") {
    context->tasks_ = context->taskService_->GetTodayTasks(true);
  } else if (inputSort == "n") {
    context->tasks_ = context->taskService_->GetTodayTasks(false);
  }
  int taskNumber = 0;
  for (const auto& task : context->tasks_){
    std::cout<<taskNumber++<<": "<<task.GetName()<<std::endl;
  }
}

std::shared_ptr<State> ShowTodayState::ReadAction() {
  return Factory::CreateState(StatesList::Base);
}
