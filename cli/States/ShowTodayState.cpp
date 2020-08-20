//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowTodayState.h"

ShowTodayState::ShowTodayState(){
  stateName_ = "show today";
  nextStates_.insert("base");
  nextStates_.insert("add subtask");
  nextStates_.insert("postpone");
  nextStates_.insert("delete");
  nextStates_.insert("exit");
}

ShowTodayState::~ShowTodayState() = default;

void ShowTodayState::Do(Context& context) {
  std::cout<<"Sort it by priority? [y/n]: ";
  std::string inputSort;
  std::getline(std::cin, inputSort);
  if (inputSort == "y") {
    context.taskService_->GetTodayTasks(true);
  } else if (inputSort == "n") {
    context.taskService_->GetTodayTasks(false);
  }
}
