// Created by valeriisudakov on 25.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTIDSTATE_H_
#define TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTIDSTATE_H_
#include "State.h"

class InputIDState : public State{
 public:
  InputIDState();
  ~InputIDState();

 public:
  StateOperationResult  Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) override;
};

#endif //TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTIDSTATE_H_
