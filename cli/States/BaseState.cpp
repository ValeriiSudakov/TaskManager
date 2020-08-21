//
// Created by valeriisudakov on 18.08.20.
//

#include "BaseState.h"
BaseState::BaseState() {
  stateName_ = "base";
  nextStates_.insert("add task");
  nextStates_.insert("add subtask");
  nextStates_.insert("show all");
  nextStates_.insert("show today");
  nextStates_.insert("show this week");
  nextStates_.insert("show by name");
  nextStates_.insert("show by label");
  nextStates_.insert("postpone");
  nextStates_.insert("delete");
  nextStates_.insert("complete");
  nextStates_.insert("exit");
}

BaseState::~BaseState() = default;

void BaseState::Do(Context& context){
  //is waiting
}
