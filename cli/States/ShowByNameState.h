//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_SHOWBYNAMESTATE_H_
#define TASKMANAGER_CLI_STATES_SHOWBYNAMESTATE_H_
#include "State.h"

class ShowByNameState : public State {
 public:
  ShowByNameState();
  ~ShowByNameState();

 public:
  virtual void Do(Context &context) override;
  virtual void PrintActions() override;

};

#endif //TASKMANAGER_CLI_STATES_SHOWBYNAMESTATE_H_
