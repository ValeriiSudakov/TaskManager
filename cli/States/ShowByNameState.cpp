//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowByNameState.h"
#include "CorrectInput.h"

ShowByNameState::ShowByNameState(){
  stateName_ = "show all by name";
  nextStates_.insert("base");
  nextStates_.insert("add subtask");
  nextStates_.insert("complete");
  nextStates_.insert("postpone");
  nextStates_.insert("delete");
  nextStates_.insert("exit");
}

ShowByNameState::~ShowByNameState() = default;

void ShowByNameState::Do(Context& context) {
  std::cout<<"Input name: ";
  auto inputName = CorrectInput::Name();
  if (!inputName.has_value()){
    std::cout<<"Name must be non-empty.\n";
    return;
  }

  std::cout<<"Sort it by priority? [y/n]: ";
  std::string inputSort;
  std::getline(std::cin, inputSort);

  std::vector<TaskDTO> result;
  if (inputSort == "y") {
    result =  context.taskService_->GetTasksByName(inputName.value(), true);
  } else if (inputSort == "n") {
    result = context.taskService_->GetTasksByName(inputName.value(), false);
  }

  for (const auto& task : result){
    std::cout<<std::endl<<task.ToString()<<std::endl;
  }
}