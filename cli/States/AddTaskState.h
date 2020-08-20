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
  virtual void      Do(Context& context) override;
  virtual void      PrintActions() override;
};

#endif //TASKMANAGER_CLI_STATES_ADDTASKSTATE_H_
