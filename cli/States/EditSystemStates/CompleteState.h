//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_COMPLETESTATE_H_
#define TASKMANAGER_CLI_STATES_COMPLETESTATE_H_
#include "States/State.h"

class CompleteState : public State {
 public:
  CompleteState();
  ~CompleteState();

 public:
  void                        Do(Context& context) override;
  std::shared_ptr<State>      ReadAction() override;
};

#endif //TASKMANAGER_CLI_STATES_COMPLETESTATE_H_
