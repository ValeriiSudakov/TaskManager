//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_COMPLETESTATE_H_
#define TASKMANAGER_CLI_STATES_COMPLETESTATE_H_
#include "State.h"

class CompleteState : public State {
 public:
  CompleteState();
  ~CompleteState();

 public:
  virtual void      Do(Context& context) override;
  virtual void      PrintActions() override;
};

#endif //TASKMANAGER_CLI_STATES_COMPLETESTATE_H_
