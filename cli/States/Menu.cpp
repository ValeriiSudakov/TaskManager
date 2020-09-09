//
// Created by valeriisudakov on 18.08.20.
//

#include "Menu.h"
#include "Factory/Factory.h"


Menu::Menu() : State(StatesID::Menu){
    actions_.insert(std::make_pair("add task",      StatesID::AddTask));
    actions_.insert(std::make_pair("add subtask",   StatesID::AddSubtask));
    actions_.insert(std::make_pair("remove",        StatesID::Delete));
    actions_.insert(std::make_pair("complete",      StatesID::Complete));
    actions_.insert(std::make_pair("postpone",      StatesID::Postpone));
    actions_.insert(std::make_pair("show by id",    StatesID::ShowByID));
    actions_.insert(std::make_pair("show all",      StatesID::ShowAll));
    actions_.insert(std::make_pair("show today",    StatesID::ShowToday));
    actions_.insert(std::make_pair("show this week", StatesID::ShowThisWeek));
    actions_.insert(std::make_pair("show by name",  StatesID::ShowByName));
    actions_.insert(std::make_pair("show by label", StatesID::ShowByLabel));
    actions_.insert(std::make_pair("exit",          StatesID::Exit));
}

Menu::~Menu() = default;


StateOperationResult Menu::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO){
  return StateOperationResult::SUCCESS;
}

void Menu::PrintNextStates(const IO_LayerInterface& io) const {
  for (const auto& action : actions_){
      io.Output(action.first + "\n");
  }
}

std::shared_ptr<State> Menu::ReadAction() {
  IO_Layer io;
  PrintNextStates(io);

  std::string output {"input command: "};
  io.Output(output);

  std::string input { io.Input() };
  for (const auto& action : actions_){
    if (action.first == input){
        return std::move(Factory::CreateState(action.second));
    }
  }
  return std::move(Factory::CreateState(GetStateID()));
}
