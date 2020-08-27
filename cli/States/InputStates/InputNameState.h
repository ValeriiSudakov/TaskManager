//
// Created by valeriisudakov on 21.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTNAMESTATE_H_
#define TASKMANAGER_CLI_STATES_INPUTNAMESTATE_H_
#include "States/InputStates/InputState.h"

class InputNameState : public InputState{
 public:
  InputNameState();
  ~InputNameState();

 public:
  bool  Do(const std::shared_ptr<Context>& context) override;
};

#endif //TASKMANAGER_CLI_STATES_INPUTNAMESTATE_H_
