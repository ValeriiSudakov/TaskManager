//
// Created by valeriisudakov on 12.10.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTFILENAMESTATE_H_
#define TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTFILENAMESTATE_H_
#include "State.h"
class InputFileNameState : public State {
 public:
  InputFileNameState();
  ~InputFileNameState();

 public:
  StateOperationResult          Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) override;
};

#endif //TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTFILENAMESTATE_H_
