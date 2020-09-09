//
// Created by valeriisudakov on 09.09.20.
//

#ifndef TASKMANAGER_CLI_STATES_MENUS_CONTINUEMENU_H_
#define TASKMANAGER_CLI_STATES_MENUS_CONTINUEMENU_H_
#include "States/Menus/Menu.h"

 class ContinueMenu : public Menu{
   public:
   ContinueMenu() : Menu(StatesID::ContinueMenu) {
     actions_.insert(std::make_pair("add subtask", StatesID::AddSubtask));
     actions_.insert(std::make_pair("remove", StatesID::Delete));
     actions_.insert(std::make_pair("complete", StatesID::Complete));
     actions_.insert(std::make_pair("postpone", StatesID::Postpone));
     actions_.insert(std::make_pair("show by id", StatesID::ShowByID));
     actions_.insert(std::make_pair("to base menu", StatesID::Exit));
   }
    ~ContinueMenu() = default;
};
#endif //TASKMANAGER_CLI_STATES_MENUS_CONTINUEMENU_H_
