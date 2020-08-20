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
  std::cout<<stateName_<<" is doing smth\n";
}

void ShowAllState::PrintActions() {}