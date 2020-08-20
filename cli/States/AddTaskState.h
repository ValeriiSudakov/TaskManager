//
// Created by valeriisudakov on 18.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_ADDTASKSTATE_H_
#define TASKMANAGER_CLI_STATES_ADDTASKSTATE_H_
#include "State.h"

class AddTaskState : public State {
 public:
  AddTaskState();
  ~AddTaskState();

 public:
  void      Do(Context& context) override;
  void      PrintActions() override;
};

#endif //TASKMANAGER_CLI_STATES_ADDTASKSTATE_H_
