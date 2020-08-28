//
// Created by valeriisudakov on 18.08.20.
//

#include "BaseState.h"
#include "Factory.h"


BaseState::BaseState() {
  stateID_ = StatesID::Base;
}

BaseState::~BaseState() = default;


StateOperationResult BaseState::Do(const std::shared_ptr<Context>& context){
  return StateOperationResult::SUCCESS;
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
  std::cout<<"input command: ";
  std::string input;

  std::getline(std::cin, input);
  if (input == "add task"){
    return std::move(Factory::CreateState(StatesID::AddTask));

  } else if (input == "add subtask") {
    return std::move(Factory::CreateState(StatesID::AddSubtask));

  } else if (input == "show all"){
    return std::move(Factory::CreateState(StatesID::ShowAll));

  } else if (input == "show this week"){
    return std::move(Factory::CreateState(StatesID::ShowThisWeek));

  } else if (input == "show by ID"){
    return std::move(Factory::CreateState(StatesID::ShowByID));

  } else if (input == "show by name"){
    return std::move(Factory::CreateState(StatesID::ShowByName));

  } else if (input == "show today"){
    return std::move(Factory::CreateState(StatesID::ShowToday));

  } else if (input == "show by label"){
    return std::move(Factory::CreateState(StatesID::ShowByLabel));

  } else if (input == "postpone"){
    return std::move(Factory::CreateState(StatesID::Postpone));

  } else if (input == "remove"){
    return std::move(Factory::CreateState(StatesID::Delete));

  } else if (input == "complete") {
    return std::move(Factory::CreateState(StatesID::Complete));

  } else if (input == "exit"){
    return nullptr;
  }
  else {
    return std::move(std::make_shared<BaseState>());
  }
}
