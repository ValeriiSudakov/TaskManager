//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowAllState.h"
#include "States/BaseState.h"
#include "Factory.h"

ShowAllState::ShowAllState(){
  stateName_ = "show all";
}

ShowAllState::~ShowAllState() = default;

void ShowAllState::Do(const std::shared_ptr<Context>& context) {
  std::cout<<"Sort tasks by priority? [y/n]: ";
  std::string inputSort;
  std::getline(std::cin, inputSort);
  context->tasks_.clear();
  if (inputSort == "y") {
    context->tasks_ = context->taskService_->GetTasks(true);
  } else if (inputSort == "n") {
    context->tasks_ = context->taskService_->GetTasks(false);
  }
  int taskNumber = 0;
  for (const auto& task : context->tasks_){
    std::cout<<taskNumber++<<": "<<task.GetName()<<std::endl;
  }
}

std::shared_ptr<State> ShowAllState::ReadAction() {
  return Factory::CreateState(StatesList::Base);
}