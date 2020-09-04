//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_SHOWTHISWEEKSTATE_H_
#define TASKMANAGER_CLI_STATES_SHOWTHISWEEKSTATE_H_
#include "States/State.h"

class ShowThisWeekState : public State {
 public:
  ShowThisWeekState();
  ~ShowThisWeekState();

 public:
  StateOperationResult        Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) override;
  std::shared_ptr<State>      ReadAction() override;
};

#endif //TASKMANAGER_CLI_STATES_SHOWTHISWEEKSTATE_H_