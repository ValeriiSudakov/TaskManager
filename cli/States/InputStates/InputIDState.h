//
// Created by valeriisudakov on 25.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTIDSTATE_H_
#define TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTIDSTATE_H_
#include "States/InputStates/InputState.h"

class InputIDState : public InputState{
 public:
  InputIDState();
  ~InputIDState();

 public:
  bool  Do(const std::shared_ptr<Context>& context) override;
};

#endif //TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTIDSTATE_H_
