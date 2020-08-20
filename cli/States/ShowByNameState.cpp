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
  std::cout<<stateName_<<" is doing smth\n";
}

void ShowByNameState::PrintActions() {}
