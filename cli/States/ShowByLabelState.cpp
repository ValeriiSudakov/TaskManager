//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowByLabelState.h"

ShowByLabelState::ShowByLabelState(){
  stateName_ = "show by label";
  nextStates_.insert("base");
  nextStates_.insert("add subtask");
  nextStates_.insert("postpone");
  nextStates_.insert("delete");
  nextStates_.insert("exit");
}

ShowByLabelState::~ShowByLabelState() = default;

void ShowByLabelState::Do(Context& context) {
  std::cout<<"Input label: ";
  std::string inputLabel;
  std::getline(std::cin, inputLabel);

  std::cout<<"Sort it by priority? [y/n]: ";
  std::string inputSort;
  std::getline(std::cin, inputSort);

  std::vector<TaskDTO> result;
  if (inputSort == "y") {
    result = context.taskService_->GetTasksByLabel(inputLabel, true);
  } else if (inputSort == "n") {
    result = context.taskService_->GetTasksByLabel(inputLabel, false);
  }
  for (const auto& task : result){
    std::cout<<std::endl<<task.ToString()<<std::endl;
  }
}