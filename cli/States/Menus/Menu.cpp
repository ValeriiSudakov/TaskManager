//
// Created by valeriisudakov on 09.09.20.
//

#include "Menu.h"
#include "InputOutputConsoleLayer.h"
#include "States/ShowStates/ShowState.h"
#include "States/EditSystemStates/EditState.h"
#include "Factory/Factory.h"


std::shared_ptr<State> Menu::ReadAction() {
  InputOutputConsoleLayer io;
  PrintNextStates(io);

  io.Output({"Input command: "});
  std::string input { io.Input() };
  if (input == actions_->exit_.first){
    return std::move(Factory::CreateState(actions_->exit_.second));
  }
  for (const auto& action : actions_->show_) {
    if (input == action.first) {
      return std::make_shared<ShowState>(action.second);
    }
  }
  for (const auto& action : actions_->edit_){
    if (input == action.first){
      return std::make_shared<EditState>(action.second);
    }
  }

  return std::move(Factory::CreateState(GetStateID()));
}

void Menu::PrintNextStates(InputOutputLayer& io) const {
  io.Output({"\n"});
  for (const auto& action : actions_->edit_){
    io.Output({action.first + "\n"});
  }
  for (const auto& action : actions_->show_){
    io.Output({action.first + "\n"});
  }
  io.Output({actions_->exit_.first + "\n"});
}

StateOperationResult Menu::Do(const std::shared_ptr<Context> &context, InputOutputLayer& io) {
  return StateOperationResult::SUCCESS;
}