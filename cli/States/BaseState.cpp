//
// Created by valeriisudakov on 18.08.20.
//

#include "BaseState.h"
#include "AddTaskState.h"
BaseState::BaseState(std::string name, std::shared_ptr<Context> context){
  stateName_ = name;
  context_ = context;
}
BaseState::~BaseState() = default;

void BaseState::Do(){ }

void BaseState::PrintActions(){
  std::cout<<"Add task"<<std::endl;
  std::cout<<"Add subtask"<<std::endl;
  std::cout<<"Show all"<<std::endl;
  std::cout<<"Show today"<<std::endl;
  std::cout<<"Show this week"<<std::endl;
  std::cout<<"Show by name"<<std::endl;
  std::cout<<"Show by label"<<std::endl;
  std::cout<<"Postpone"<<std::endl;
  std::cout<<"Delete"<<std::endl;
  std::cout<<"Complete"<<std::endl;
}

void BaseState::ReadAction() {
  std::string input;
  std::cout<<"Input action: ";
  std::getline(std::cin, input);

  if (input == "Add task"){
    auto newState = AddTaskState("Add task", context_);
    newState.Do();
    context_->TransitionTo(std::make_shared<AddTaskState>("add task", context_));
  }
}