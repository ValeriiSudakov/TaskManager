//
// Created by valeriisudakov on 09.09.20.
//

#include "Factory/Factory.h"
#include "States/ShowStates/ShowState.h"
#include "BaseMenu.h"
#include "IO_Layer.h"

BaseMenu::BaseMenu() : Menu(StatesID::BaseMenu) {
  actions_.insert(std::make_pair("add task",      StatesID::AddTask));
  actions_.insert(std::make_pair("add subtask",   StatesID::AddSubtask));
  actions_.insert(std::make_pair("remove",        StatesID::Delete));
  actions_.insert(std::make_pair("complete",      StatesID::Complete));
  actions_.insert(std::make_pair("postpone",      StatesID::Postpone));
  actions_.insert(std::make_pair("show by id",    StatesID::ShowByID));
  actions_.insert(std::make_pair("show all",      StatesID::ShowAll));
  actions_.insert(std::make_pair("show this week",StatesID::ShowThisWeek));
  actions_.insert(std::make_pair("show today",    StatesID::ShowToday));
  actions_.insert(std::make_pair("show by name",  StatesID::ShowByName));
  actions_.insert(std::make_pair("show by label", StatesID::ShowByLabel));
  actions_.insert(std::make_pair("exit",          StatesID::Exit));
}

std::shared_ptr<State> BaseMenu::ReadAction() {
  IO_Layer io;
  PrintNextStates(io);

  io.Output({"Input command: "});
  std::string input { io.Input() };

  for (const auto& action : actions_){
    std::size_t found = action.first.find("show");
    if (found != std::string::npos){
      return std::move(std::make_shared<ShowState>(action.second));
    }
    else if (input == action.first){
      return std::move(Factory::CreateState(action.second));
    }
  }

  return std::move(Factory::CreateState(GetStateID()));
}