//
// Created by valeriisudakov on 27.08.20.
//

#ifndef TASKMANAGER_CLI_FINITESTATEMACHINE_H_
#define TASKMANAGER_CLI_FINITESTATEMACHINE_H_
#include "StateMachine.h"
#include <list>

class FiniteStateMachine : public StateMachine {
 public:
  FiniteStateMachine(const  std::list<StatesID>& states,
                     const std::shared_ptr<Context>& context,
                     std::unique_ptr<IO_LayerInterface> io)
                     :
                     states_(states),
                     StateMachine(std::move(context), std::move(io)) { }
  ~FiniteStateMachine() = default;

 public:
  void Execute() override;

 private:
  std::list<StatesID> states_;
};

#endif //TASKMANAGER_CLI_FINITESTATEMACHINE_H_
