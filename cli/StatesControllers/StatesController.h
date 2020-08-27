//
// Created by valeriisudakov on 19.08.20.
//

#ifndef TASKMANAGER_CLI_STATESCONTROLLER_H_
#define TASKMANAGER_CLI_STATESCONTROLLER_H_
#include "Context.h"

class State;

class StatesController {
 public:
  StatesController();
  ~StatesController();

 public:
  void ExecuteProgram();

 private:
  std::shared_ptr<Context> context_;
  std::shared_ptr<State>   state_;
};

#endif //TASKMANAGER_CLI_STATESCONTROLLER_H_
