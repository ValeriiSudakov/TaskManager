//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_ADDSUBTASK_H_
#define TASKMANAGER_CLI_STATES_ADDSUBTASK_H_
#include "State.h"
class AddSubtaskState : public State {
 public:
  AddSubtaskState();
  ~AddSubtaskState();

 public:
  void      Do(Context& context) override;
  void      PrintActions() override;
};

#endif //TASKMANAGER_CLI_STATES_ADDSUBTASK_H_
