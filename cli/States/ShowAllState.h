//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_SHOWALL_H_
#define TASKMANAGER_CLI_STATES_SHOWALL_H_
#include "State.h"

class ShowAllState : public State {
 public:
  ShowAllState();
  ~ShowAllState();

 public:
  void      Do(Context& context) override;
};
#endif //TASKMANAGER_CLI_STATES_SHOWALL_H_