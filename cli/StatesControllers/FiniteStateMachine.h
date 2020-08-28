//
// Created by valeriisudakov on 27.08.20.
//

#ifndef TASKMANAGER_CLI_FINITESTATEMACHINE_H_
#define TASKMANAGER_CLI_FINITESTATEMACHINE_H_
#include "States/State.h"
#include "States/StatesID.h"
#include <vector>
#include <map>


class FiniteStateMachine {
 public:
  FiniteStateMachine(const std::map<StatesID, std::map<StateOperationResult,
                                                            StatesID>>& stateTransitionTable,
                     StatesID firstState,
                     const std::shared_ptr<Context>& context);
  ~FiniteStateMachine();

 public:
  void Execute();

 private:
  std::shared_ptr<Context> context_;
  StatesID firstState_;
  std::map<StatesID, std::map<StateOperationResult, StatesID>> stateTransitionTable_;
};

#endif //TASKMANAGER_CLI_FINITESTATEMACHINE_H_
