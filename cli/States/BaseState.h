//
// Created by valeriisudakov on 18.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_BASESTATE_H_
#define TASKMANAGER_CLI_STATES_BASESTATE_H_
#include "State.h"

class State;

class BaseState : public State {
 public:
  BaseState();
  ~BaseState();

 public:
  void Do(Context& context) override;
  void PrintActions() override;
};

#endif //TASKMANAGER_CLI_STATES_BASESTATE_H_
