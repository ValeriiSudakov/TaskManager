//
// Created by valeriisudakov on 27.08.20.
//

#ifndef TASKMANAGER_CLI_FINITESTATEMACHINE_H_
#define TASKMANAGER_CLI_FINITESTATEMACHINE_H_
#include "StateMachine.h"
#include <list>
#include <utility>

class FiniteStateMachine : public StateMachine {
 public:
  FiniteStateMachine(std::list<StatesID>  states,
                     const std::shared_ptr<Context>& context,
                     std::shared_ptr<InputOutputLayer> io)
                     :
                     states_(std::move(states)),
                     StateMachine(context, io) { }
  ~FiniteStateMachine() = default;

 public:
  void Execute() override;

 private:
  std::list<StatesID> states_;
};

#endif //TASKMANAGER_CLI_FINITESTATEMACHINE_H_
