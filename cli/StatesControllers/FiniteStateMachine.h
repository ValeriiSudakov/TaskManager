//
// Created by valeriisudakov on 27.08.20.
//

#ifndef TASKMANAGER_CLI_FINITESTATEMACHINE_H_
#define TASKMANAGER_CLI_FINITESTATEMACHINE_H_
#include "States/State.h"
#include "States/StatesList.h"
#include <vector>


class FiniteStateMachine {
 public:
  FiniteStateMachine(const std::vector<InputStatesList>& nextStates, const std::shared_ptr<Context>& context);
  ~FiniteStateMachine();

 public:
  void Execute();

 private:
  std::shared_ptr<Context> context_;
  std::vector<InputStatesList> nextStates_;
};

#endif //TASKMANAGER_CLI_FINITESTATEMACHINE_H_
