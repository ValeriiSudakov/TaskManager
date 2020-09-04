//
// Created by valeriisudakov on 27.08.20.
//

#ifndef TASKMANAGER_CLI_FINITESTATEMACHINE_H_
#define TASKMANAGER_CLI_FINITESTATEMACHINE_H_
#include "StateMachine.h"
#include <map>

class FiniteStateMachine : public StateMachine {
 public:
  FiniteStateMachine(const std::map<StatesID, std::map<StateOperationResult,
                                                            StatesID>>& stateTransitionTable,
                     const StatesID& firstState,
                     const std::shared_ptr<Context>& context,
                     std::unique_ptr<IO_LayerInterface> io);
  ~FiniteStateMachine();

 public:
  void Execute() override;

 private:
  std::map<StatesID, std::map<StateOperationResult, StatesID>> stateTransitionTable_;
};

#endif //TASKMANAGER_CLI_FINITESTATEMACHINE_H_
