//
// Created by valeriisudakov on 04.09.20.
//

#ifndef TASKMANAGER_CLI_STATESCONTROLLERS_STATEMACHINE_H_
#define TASKMANAGER_CLI_STATESCONTROLLERS_STATEMACHINE_H_
#include "States/State.h"
#include "States/StatesID.h"
#include "IO_LayerInterface.h"

class StateMachine {
 public:
  StateMachine(const StatesID& firstState, const std::shared_ptr<Context>& context, std::unique_ptr<IO_LayerInterface> io) :
              firstState_(firstState), context_(std::move(context)), io_(std::move(io)){}

              virtual ~StateMachine() = default;

 public:
  virtual void Execute() = 0;

 protected:
  std::shared_ptr<Context> context_;
  StatesID firstState_;
  std::unique_ptr<IO_LayerInterface> io_;
};

#endif //TASKMANAGER_CLI_STATESCONTROLLERS_STATEMACHINE_H_
