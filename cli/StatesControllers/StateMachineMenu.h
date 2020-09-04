//
// Created by valeriisudakov on 04.09.20.
//

#ifndef TASKMANAGER_CLI_STATESCONTROLLERS_STATEMACHINEBASEMENU_H_
#define TASKMANAGER_CLI_STATESCONTROLLERS_STATEMACHINEBASEMENU_H_
#include "StateMachine.h"

class StateMachineMenu : public StateMachine {
 public:
  StateMachineMenu(const StatesID& firstState, const std::shared_ptr<Context>& context, std::unique_ptr<IO_LayerInterface> io);
  ~StateMachineMenu();
 public:
  void Execute() override;
};

#endif //TASKMANAGER_CLI_STATESCONTROLLERS_STATEMACHINEBASEMENU_H_
