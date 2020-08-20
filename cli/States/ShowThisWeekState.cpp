//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowThisWeekState.h"

ShowThisWeekState::ShowThisWeekState(){
  stateName_ = "show this week";
  nextStates_.insert("base");
  nextStates_.insert("add subtask");
  nextStates_.insert("postpone");
  nextStates_.insert("delete");
  nextStates_.insert("exit");
}

ShowThisWeekState::~ShowThisWeekState() = default;

void ShowThisWeekState::Do(Context& context) {
  std::cout<<stateName_<<" is doing \n";
}

void ShowThisWeekState::PrintActions() {}
