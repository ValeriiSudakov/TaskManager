//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowByNameState.h"
#include "States/BaseState.h"
ShowByNameState::ShowByNameState(){
  stateName_ = "show all by name";
}

ShowByNameState::~ShowByNameState() = default;

void ShowByNameState::Do(Context& context) {
  std::cout<<"Sort tasks by priority? [y/n]: ";
  std::string inputSort;
  std::getline(std::cin, inputSort);
  if (inputSort == "y") {
    context.tasks_ = context.taskService_->GetTasksByName(context.buffer_.name, true);
  } else if (inputSort == "n") {
    context.tasks_ = context.taskService_->GetTasksByName(context.buffer_.name, false);
  }
  int taskNumber = 0;
  for (const auto& task : context.tasks_){
    std::cout<<taskNumber++<<": "<<task.GetName()<<std::endl;
  }
}

std::shared_ptr<State> ShowByNameState::ReadAction() {
  return std::make_shared<BaseState>();
}