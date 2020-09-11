//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_SHOWBYNAMESTATE_H_
#define TASKMANAGER_CLI_STATES_SHOWBYNAMESTATE_H_
#include "States/State.h"

class ShowByNameState : public State {
 public:
  ShowByNameState();
  ~ShowByNameState();

 public:
  StateOperationResult        Do(const std::shared_ptr<Context>& context, const InputOutputLayer& IO) override;
};

#endif //TASKMANAGER_CLI_STATES_SHOWBYNAMESTATE_H_
