//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_SHOWTODAYSTATE_H_
#define TASKMANAGER_CLI_STATES_SHOWTODAYSTATE_H_
#include "States/State.h"

class ShowTodayState :  public State {
 public:
  ShowTodayState();
  ~ShowTodayState();

 public:
  void                        Do(Context& context) override;
  std::shared_ptr<State>      ReadAction() override;
};

#endif //TASKMANAGER_CLI_STATES_SHOWTODAYSTATE_H_
