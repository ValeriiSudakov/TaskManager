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
  StateOperationResult        Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) override;
};

#endif //TASKMANAGER_CLI_STATES_SHOWTODAYSTATE_H_
