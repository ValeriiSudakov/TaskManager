//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_ADDSUBTASK_H_
#define TASKMANAGER_CLI_STATES_ADDSUBTASK_H_
#include "States/State.h"

class AddSubtaskState : public State {
 public:
  AddSubtaskState();
  ~AddSubtaskState();

 public:
  StateOperationResult        Do(const std::shared_ptr<Context>& context) override;
  std::shared_ptr<State>      ReadAction() override;
};

#endif //TASKMANAGER_CLI_STATES_ADDSUBTASK_H_
