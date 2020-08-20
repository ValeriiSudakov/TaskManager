//
// Created by valeriisudakov on 18.08.20.
//

#include "State.h"
#include "StatesFactory.h"
#include "Context.h"

State::~State() = default;

void State::PrintState(){
  std::cout<<stateName_<<std::endl;
}

void State::PrintNextStates_() {
  for (const auto& state : nextStates_){
    std::cout<<state<<std::endl;
  }
}

std::unique_ptr<State> State::ReadAction() {
  PrintNextStates_();
  std::string input;
  std::cout<<"Choose action: ";
  std::getline(std::cin, input);
  return std::move(StatesFactory::Create(input));
}