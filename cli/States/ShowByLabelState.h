//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_SHOWBYLABELSTATE_H_
#define TASKMANAGER_CLI_STATES_SHOWBYLABELSTATE_H_
#include "State.h"

class ShowByLabelState : public State {
 public:
  ShowByLabelState();
  ~ShowByLabelState();

 public:
  void     Do(Context& context) override;
  void     PrintActions() override;

};
#endif //TASKMANAGER_CLI_STATES_SHOWBYLABELSTATE_H_
