//
// Created by valeriisudakov on 20.08.20.
//

#include "DeleteState.h"
#include "CorrectInput.h"

DeleteState::DeleteState(){
  stateName_ = "delete";
  nextStates_.insert("base");
  nextStates_.insert("exit");
}

DeleteState::~DeleteState() = default;

void DeleteState::Do(Context& context) {
  std::cout<<"Input number of task to delete: ";
  auto number = CorrectInput::Number();
  if (!number.has_value()){
    std::cout<<"Incorrect input of number.\n";
    return;
  }
}
