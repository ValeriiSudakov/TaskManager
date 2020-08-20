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

void ShowByLabelState::Do(Context &context) {
  std::cout<<stateName_<<" is doing \n";
}

void ShowByLabelState::PrintActions() {}