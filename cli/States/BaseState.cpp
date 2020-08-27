//
// Created by valeriisudakov on 18.08.20.
//

#include "BaseState.h"
#include "Factory.h"


BaseState::BaseState() {
  stateName_ = "base";
}

BaseState::~BaseState() = default;

void BaseState::Do(const std::shared_ptr<Context>& context){
  //is waiting
}

void BaseState::PrintNextStates() {
  std::cout<<"add task"<<std::endl;
  std::cout<<"add subtask"<<std::endl;
  std::cout<<"show by ID"<<std::endl;
  std::cout<<"show all"<<std::endl;
  std::cout<<"show today"<<std::endl;
  std::cout<<"show this week"<<std::endl;
  std::cout<<"show by name"<<std::endl;
  std::cout<<"show by label"<<std::endl;
  std::cout<<"postpone"<<std::endl;
  std::cout<<"remove"<<std::endl;
  std::cout<<"complete"<<std::endl;
  std::cout<<"exit"<<std::endl;
}

std::shared_ptr<State> BaseState::ReadAction() {
  PrintNextStates();
  std::cout<<"input next state: ";
  std::string input;

  std::getline(std::cin, input);
  if (input == "add task"){
    return std::move(Factory::CreateState(StatesList::AddTask));

  } else if (input == "add subtask") {
    return std::move(Factory::CreateState(StatesList::AddSubtask));

  } else if (input == "show all"){
    return std::move(Factory::CreateState(StatesList::ShowAll));

  } else if (input == "show this week"){
    return std::move(Factory::CreateState(StatesList::ShowThisWeek));

  } else if (input == "show by ID"){
    return std::move(Factory::CreateState(StatesList::ShowByID));

  } else if (input == "show by name"){
    return std::move(Factory::CreateState(StatesList::ShowByName));

  } else if (input == "show today"){
    return std::move(Factory::CreateState(StatesList::ShowToday));

  } else if (input == "show by label"){
    return std::move(Factory::CreateState(StatesList::ShowByLabel));

  } else if (input == "postpone"){
    return std::move(Factory::CreateState(StatesList::Postpone));

  } else if (input == "remove"){
    return std::move(Factory::CreateState(StatesList::Delete));

  } else if (input == "complete") {
    return std::move(Factory::CreateState(StatesList::Complete));

  } else if (input == "exit"){
    return nullptr;
  }
  else {
    return std::move(std::make_shared<BaseState>());
  }
}
