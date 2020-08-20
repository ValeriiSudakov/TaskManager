//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_SHOWTODAYSTATE_H_
#define TASKMANAGER_CLI_STATES_SHOWTODAYSTATE_H_
#include "State.h"

class ShowTodayState :  public State {
 public:
  ShowTodayState();
  ~ShowTodayState();

 public:
  virtual void Do(Context &context) override;
  virtual void PrintActions() override;
};

#endif //TASKMANAGER_CLI_STATES_SHOWTODAYSTATE_H_
