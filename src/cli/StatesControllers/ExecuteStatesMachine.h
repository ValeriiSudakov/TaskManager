//
// Created by valeriisudakov on 27.08.20.
//

#ifndef TASKMANAGER_CLI_FINITESTATEMACHINE_H_
#define TASKMANAGER_CLI_FINITESTATEMACHINE_H_
#include "StateMachine.h"
#include <vector>
#include <utility>

class ExecuteStatesMachine : public StateMachine {
 public:
  ExecuteStatesMachine(std::vector<StatesID> states,
                       const std::shared_ptr<Context>& context,
                       InputOutputLayer& io)
                     :
                     states_(std::move(states)),
                     StateMachine(context, io) { }
  ~ExecuteStatesMachine() = default;

 public:
  void Execute() override;

 private:
  std::vector<StatesID> states_;
};

#endif //TASKMANAGER_CLI_FINITESTATEMACHINE_H_
