//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_COMPLETESTATE_H_
#define TASKMANAGER_CLI_STATES_COMPLETESTATE_H_
#include "State.h"

class CompleteState : public State {
 public:
  CompleteState();
  ~CompleteState();

 public:
  StateOperationResult        Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) override;
};

#endif //TASKMANAGER_CLI_STATES_COMPLETESTATE_H_
