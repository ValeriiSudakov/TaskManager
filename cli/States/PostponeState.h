//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_POSTPONESTATE_H_
#define TASKMANAGER_CLI_STATES_POSTPONESTATE_H_
#include "State.h"

class PostponeState : public State {
 public:
  PostponeState();
  ~PostponeState();

 public:
  void      Do(Context& context) override;
};

#endif //TASKMANAGER_CLI_STATES_POSTPONESTATE_H_
