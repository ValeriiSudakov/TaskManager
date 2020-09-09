//
// Created by valeriisudakov on 18.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_BASESTATE_H_
#define TASKMANAGER_CLI_STATES_BASESTATE_H_
#include "States/Menus/Menu.h"

class BaseMenu : public Menu {
 public:
  BaseMenu();
  ~BaseMenu() = default;

  std::shared_ptr<State> ReadAction() override;

};

#endif //TASKMANAGER_CLI_STATES_BASESTATE_H_
