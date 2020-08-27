//
// Created by valeriisudakov on 21.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTLABELSTATE_H_
#define TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTLABELSTATE_H_
#include "States/InputStates/InputState.h"


class InputLabelState :  public InputState{
 public:
  InputLabelState();
  ~InputLabelState();

 public:
  bool  Do(const std::shared_ptr<Context>& context) override;
};

#endif //TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTLABELSTATE_H_
