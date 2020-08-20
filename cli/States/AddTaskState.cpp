//
// Created by valeriisudakov on 18.08.20.
//

#include "AddTaskState.h"

AddTaskState::AddTaskState() {
  stateName_ = "add task";
  nextStates_.insert("base");
  nextStates_.insert("exit");
}

AddTaskState::~AddTaskState() = default;

//void AddTaskState::PrintActions() {
//  std::cout<<"Input:\nTask name;\nTask label;\nTask priority: First; Second; Third; None\nDate: year-mon-date\n";
//}

void AddTaskState::Do(Context& context){
  std::cout<<stateName_<<" is doing smth\n";
  //context_.lock()->SetState(std::make_shared<BaseState>(context_));
}

void AddTaskState::PrintActions() {}