//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_SHOWBYLABELSTATE_H_
#define TASKMANAGER_CLI_STATES_SHOWBYLABELSTATE_H_
#include "States/State.h"

class ShowByLabelState : public State {
 public:
  ShowByLabelState();
  ~ShowByLabelState();

 public:
  StateOperationResult       Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) override;
};
#endif //TASKMANAGER_CLI_STATES_SHOWBYLABELSTATE_H_
