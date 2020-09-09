//
// Created by valeriisudakov on 09.09.20.
//

#include "Menu.h"
#include "IO_Layer.h"
#include "Factory/Factory.h"
StateOperationResult Menu::Do(const std::shared_ptr<Context> &context, const IO_LayerInterface &IO) {}

std::shared_ptr<State> Menu::ReadAction() {
  IO_Layer io;
  PrintNextStates(io);

  io.Output({"Input command: "});
  std::string input { io.Input() };

  for (const auto& action : actions_){
    if (input == action.first){
      return std::move(Factory::CreateState(action.second));
    }
  }
  return std::move(Factory::CreateState(GetStateID()));
}

void Menu::PrintNextStates(const IO_LayerInterface &io) const {
  for (const auto& action : actions_){
    io.Output(action.first + "\n");
  }
}