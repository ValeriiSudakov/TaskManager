//
// Created by valeriisudakov on 18.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_ADDTASKSTATE_H_
#define TASKMANAGER_CLI_STATES_ADDTASKSTATE_H_
#include "States/State.h"

class AddTaskState : public State {
 public:
  AddTaskState();
  ~AddTaskState();

 public:
  void                        Do(const std::shared_ptr<Context>& context) override;
  std::shared_ptr<State>      ReadAction() override;
};

#endif //TASKMANAGER_CLI_STATES_ADDTASKSTATE_H_
