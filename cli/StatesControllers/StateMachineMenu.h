//
// Created by valeriisudakov on 04.09.20.
//

#ifndef TASKMANAGER_CLI_STATESCONTROLLERS_STATEMACHINEBASEMENU_H_
#define TASKMANAGER_CLI_STATESCONTROLLERS_STATEMACHINEBASEMENU_H_
#include "StateMachine.h"

class StateMachineMenu : public StateMachine {
 public:
  ~StateMachineMenu() = default;

  StateMachineMenu(const StatesID& menuID, const std::shared_ptr<Context>& context, std::shared_ptr<InputOutputLayer> io) :
                  menuID_(menuID), StateMachine(context, io) {}
 public:
  void Execute() override;

 private:
  StatesID menuID_;
};

#endif //TASKMANAGER_CLI_STATESCONTROLLERS_STATEMACHINEBASEMENU_H_
