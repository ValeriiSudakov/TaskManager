//
// Created by valeriisudakov on 10.09.20.
//

#ifndef TASKMANAGER_CLI_STATES_MENUS_MENUACTIONS_H_
#define TASKMANAGER_CLI_STATES_MENUS_MENUACTIONS_H_
#include <map>
#include "States/StatesID.h"

struct Actions{
  std::map<std::string, StatesID>   edit_;
  std::map<std::string, StatesID>   show_;
  std::pair<std::string, StatesID>  exit_;
};
#endif //TASKMANAGER_CLI_STATES_MENUS_MENUACTIONS_H_
