//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowByLabelState.h"
#include "States/BaseState.h"
#include "Factory.h"

ShowByLabelState::ShowByLabelState(){
  stateName_ = "show by label";
}

ShowByLabelState::~ShowByLabelState() = default;

void ShowByLabelState::Do(const std::shared_ptr<Context>& context) {
  std::cout<<"Sort tasks by priority? [y/n]: ";
  std::string inputSort;
  std::getline(std::cin, inputSort);
  if (inputSort == "y") {
    context->tasks_ = context->taskService_->GetTasksByLabel(context->buffer_.label, true);
  } else if (inputSort == "n") {
    context->tasks_ = context->taskService_->GetTasksByLabel(context->buffer_.label, false);
  }
  int taskNumber = 0;
  for (const auto& task : context->tasks_){
    std::cout<<taskNumber++<<": "<<task.GetName()<<std::endl;
  }
}

std::shared_ptr<State> ShowByLabelState::ReadAction() {
  return Factory::CreateState(StatesList::Base);
}
