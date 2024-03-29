//
// Created by valeriisudakov on 21.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTPRIORITYSTATE_H_
#define TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTPRIORITYSTATE_H_
#include "State.h"

class InputPriorityState : public State{
 public:
  InputPriorityState();
  ~InputPriorityState();

 public:
  StateOperationResult  Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) override;
};

#endif //TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTPRIORITYSTATE_H_
