//
// Created by valeriisudakov on 21.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTNAMESTATE_H_
#define TASKMANAGER_CLI_STATES_INPUTNAMESTATE_H_
#include "States/State.h"

class InputNameState : public State{
 public:
  InputNameState();
  ~InputNameState();

 public:
  StateOperationResult          Do(const std::shared_ptr<Context>& context, const InputOutputLayer& io) override;
};

#endif //TASKMANAGER_CLI_STATES_INPUTNAMESTATE_H_
