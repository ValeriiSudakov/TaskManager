//
// Created by valeriisudakov on 18.08.20.
//

#include "AddTaskState.h"

AddTaskState::AddTaskState(std::string name, std::shared_ptr<Context> context) {
  stateName_ = name;
  context_ = context;
}

AddTaskState::~AddTaskState() = default;

void AddTaskState::PrintActions() {
  std::cout<<"Input:\nTask name;\nTask label;\nTask priority: First; Second; Third; None\nDate: year-mon-date\n";
}

void AddTaskState::ReadAction() {

}

void AddTaskState::Do(){
  std::cout<<stateName_<<" is doing smth\n";
  //std::string name;
  //std::getline(std::cin, name);
  //if (name == ""){
  //  std::cout<<"Name must be not empty";
  //}
}