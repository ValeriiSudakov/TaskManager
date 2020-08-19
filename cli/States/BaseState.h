//
// Created by valeriisudakov on 18.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_BASESTATE_H_
#define TASKMANAGER_CLI_STATES_BASESTATE_H_
#include "State.h"

class BaseState : public State {
 public:
  BaseState(std::string name, std::shared_ptr<Context> context);
  ~BaseState();

 public:
  void Do() override;
  void PrintActions() override;
  void ReadAction() override;
};

#endif //TASKMANAGER_CLI_STATES_BASESTATE_H_
