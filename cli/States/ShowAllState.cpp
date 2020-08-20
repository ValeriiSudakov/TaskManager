//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowAllState.h"

ShowAllState::ShowAllState(){
  stateName_ = "show all";
  nextStates_.insert("base");
  nextStates_.insert("add subtask");
  nextStates_.insert("postpone");
  nextStates_.insert("delete");
  nextStates_.insert("exit");
}

ShowAllState::~ShowAllState() = default;

void ShowAllState::Do(Context& context) {
  std::cout<<"Sort it by priority? [y/n]: ";
  std::string inputSort;
  std::getline(std::cin, inputSort);

  std::vector<TaskDTO> result;
  if (inputSort == "y") {
    result = context.taskService_->GetTasks(true);
  } else if (inputSort == "n") {
    result = context.taskService_->GetTasks(false);
  }
  for (const auto& task : result){
    std::cout<<std::endl<<task.ToString()<<std::endl;
  }
}
