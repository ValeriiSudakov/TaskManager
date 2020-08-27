//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_POSTPONESTATE_H_
#define TASKMANAGER_CLI_STATES_POSTPONESTATE_H_
#include "States/State.h"

class PostponeState : public State {
 public:
  PostponeState();
  ~PostponeState();

 public:
  void                        Do(const std::shared_ptr<Context>& context) override;
  std::shared_ptr<State>      ReadAction() override;
};

#endif //TASKMANAGER_CLI_STATES_POSTPONESTATE_H_
