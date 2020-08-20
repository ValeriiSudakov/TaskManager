//
// Created by valeriisudakov on 20.08.20.
//

#include "AddSubtaskState.h"

AddSubtaskState::AddSubtaskState() {
  stateName_ = "add subtask";
  nextStates_.insert("base");
  nextStates_.insert("exit");
}

AddSubtaskState::~AddSubtaskState() = default;

void AddSubtaskState::Do(Context& context) {
  std::cout<<stateName_<<" is doing \n";
}

void AddSubtaskState::PrintActions() {}