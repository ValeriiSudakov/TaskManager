//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_DELETESTATE_H_
#define TASKMANAGER_CLI_STATES_DELETESTATE_H_
#include "State.h"

class DeleteState : public State {
 public:
  DeleteState();
  ~DeleteState();

 public:
  virtual void      Do(Context& context) override;
  virtual void      PrintActions() override;
};

#endif //TASKMANAGER_CLI_STATES_DELETESTATE_H_
