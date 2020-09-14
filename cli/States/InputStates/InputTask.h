//
// Created by valeriisudakov on 01.09.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTTASK_H_
#define TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTTASK_H_
#include "States/State.h"
class InputTask : public State{
public:
  InputTask();
  ~InputTask();

public:
  StateOperationResult  Do(const std::shared_ptr<Context>& context, std::shared_ptr<InputOutputLayer> io) override;
};

#endif //TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTTASK_H_
