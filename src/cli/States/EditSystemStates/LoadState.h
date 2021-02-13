//
// Created by valeriisudakov on 05.10.20.
//

#ifndef TASKMANAGER_CLI_STATES_EDITSYSTEMSTATES_LOADSTATE_H_
#define TASKMANAGER_CLI_STATES_EDITSYSTEMSTATES_LOADSTATE_H_
#include "States/State.h"
class LoadState : public State {
  public:
  LoadState();
  ~LoadState();

  public:
  StateOperationResult        Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) override;
};

#endif //TASKMANAGER_CLI_STATES_EDITSYSTEMSTATES_LOADSTATE_H_
