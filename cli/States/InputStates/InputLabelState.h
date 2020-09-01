//
// Created by valeriisudakov on 21.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTLABELSTATE_H_
#define TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTLABELSTATE_H_
#include "States/State.h"


class InputLabelState :  public State{
 public:
  InputLabelState();
  ~InputLabelState();

 public:
  StateOperationResult  Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) override;
};

#endif //TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTLABELSTATE_H_
