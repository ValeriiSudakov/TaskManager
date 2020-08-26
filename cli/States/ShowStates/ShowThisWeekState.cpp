//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowThisWeekState.h"
#include "States/BaseState.h"

ShowThisWeekState::ShowThisWeekState(){
  stateName_ = "show this week";
}

ShowThisWeekState::~ShowThisWeekState() = default;

void ShowThisWeekState::Do(Context& context) {
  std::cout<<"Sort tasks by priority? [y/n]: ";
  std::string inputSort;
  std::getline(std::cin, inputSort);
  if (inputSort == "y") {
    context.tasks_ = context.taskService_->GetWeekTasks(true);
  } else if (inputSort == "n") {
    context.tasks_ = context.taskService_->GetWeekTasks(false);
  }
  int taskNumber = 0;
  for (const auto& task : context.tasks_){
    std::cout<<taskNumber++<<": "<<task.GetName()<<std::endl;
  }
}

std::shared_ptr<State> ShowThisWeekState::ReadAction() {
  return std::make_shared<BaseState>();
}
