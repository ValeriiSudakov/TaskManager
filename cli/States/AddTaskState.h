//
// Created by valeriisudakov on 18.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_ADDTASKSTATE_H_
#define TASKMANAGER_CLI_STATES_ADDTASKSTATE_H_
#include "State.h"

class AddTaskState : public State {
 public:
  AddTaskState(std::string name, std::shared_ptr<Context> context);
  ~AddTaskState();

 public:
  void PrintActions() override;
  void ReadAction() override;
  void Do() override;
};

#endif //TASKMANAGER_CLI_STATES_ADDTASKSTATE_H_
