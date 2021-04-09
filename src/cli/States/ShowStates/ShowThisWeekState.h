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
  StateOperationResult        Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) override;
};

#endif //TASKMANAGER_CLI_STATES_SHOWTHISWEEKSTATE_H_
