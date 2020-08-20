//
// Created by valeriisudakov on 20.08.20.
//

#include "DeleteState.h"

DeleteState::DeleteState(){
  stateName_ = "delete";
  nextStates_.insert("base");
  nextStates_.insert("exit");
}

DeleteState::~DeleteState() = default;

void DeleteState::Do(Context& context) {
  std::cout<<stateName_<<" is doing smth\n";
}
