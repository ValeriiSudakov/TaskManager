//
// Created by valeriisudakov on 21.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTDATESTATE_H_
#define TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTDATESTATE_H_
#include "State.h"

class InputDateState : public State{
 public:
  InputDateState();
  ~InputDateState();

 public:
  StateOperationResult  Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) override;
};

#endif //TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTDATESTATE_H_
