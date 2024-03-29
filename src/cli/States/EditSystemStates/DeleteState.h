//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_DELETESTATE_H_
#define TASKMANAGER_CLI_STATES_DELETESTATE_H_
#include "State.h"

class DeleteState : public State {
 public:
  DeleteState();
  ~DeleteState();

 public:
  StateOperationResult        Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) override;
};
#endif //TASKMANAGER_CLI_STATES_DELETESTATE_H_
