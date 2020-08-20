//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_SHOWTHISWEEKSTATE_H_
#define TASKMANAGER_CLI_STATES_SHOWTHISWEEKSTATE_H_
#include "State.h"

class ShowThisWeekState : public State {
 public:
  ShowThisWeekState();
  ~ShowThisWeekState();

 public:
  void      Do(Context& context) override;
  void      PrintActions() override;
};

#endif //TASKMANAGER_CLI_STATES_SHOWTHISWEEKSTATE_H_
