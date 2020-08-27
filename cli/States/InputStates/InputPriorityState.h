//
// Created by valeriisudakov on 21.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTPRIORITYSTATE_H_
#define TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTPRIORITYSTATE_H_
#include "States/InputStates/InputState.h"

class InputPriorityState : public InputState{
 public:
  InputPriorityState();
  ~InputPriorityState();

 public:
  bool  Do(const std::shared_ptr<Context>& context) override;
};

#endif //TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTPRIORITYSTATE_H_
