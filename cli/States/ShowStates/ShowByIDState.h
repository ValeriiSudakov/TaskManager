//
// Created by valeriisudakov on 25.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_SHOWSTATES_SHOWBYIDSTATE_H_
#define TASKMANAGER_CLI_STATES_SHOWSTATES_SHOWBYIDSTATE_H_
#include "States/State.h"
class ShowByIDState : public State {
 public:
  ShowByIDState();
  ~ShowByIDState();

 public:
  StateOperationResult      Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) override;
};

#endif //TASKMANAGER_CLI_STATES_SHOWSTATES_SHOWBYIDSTATE_H_
