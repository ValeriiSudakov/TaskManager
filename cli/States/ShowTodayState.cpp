//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowTodayState.h"

ShowTodayState::ShowTodayState(){
  stateName_ = "show today";
  nextStates_.insert("base");
  nextStates_.insert("add subtask");
  nextStates_.insert("postpone");
  nextStates_.insert("delete");
  nextStates_.insert("exit");
}

ShowTodayState::~ShowTodayState() = default;

void ShowTodayState::Do(Context& context) {
  std::cout<<stateName_<<" is doing smth\n";
}

void ShowTodayState::PrintActions() {}