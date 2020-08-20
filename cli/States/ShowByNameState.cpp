//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowByNameState.h"

ShowByNameState::ShowByNameState(){
  stateName_ = "show all by name";
  nextStates_.insert("base");
  nextStates_.insert("add subtask");
  nextStates_.insert("postpone");
  nextStates_.insert("delete");
  nextStates_.insert("exit");
}

ShowByNameState::~ShowByNameState() = default;

void ShowByNameState::Do(Context& context) {
  std::cout<<"Input name: ";
  std::string inputName;
  std::getline(std::cin, inputName);

  std::cout<<"Sort it by priority? [y/n]: ";
  std::string inputSort;
  std::getline(std::cin, inputSort);
  if (inputSort == "y") {
    context.taskService_->GetTasksByName(inputName, true);
  } else if (inputSort == "n") {
    context.taskService_->GetTasksByName(inputName, false);
  }
}