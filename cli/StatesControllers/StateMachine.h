//
// Created by valeriisudakov on 04.09.20.
//

#ifndef TASKMANAGER_CLI_STATESCONTROLLERS_STATEMACHINE_H_
#define TASKMANAGER_CLI_STATESCONTROLLERS_STATEMACHINE_H_
#include "States/State.h"
#include "States/StatesID.h"
#include "InputOutputLayer.h"

class StateMachine {
 public:
  StateMachine(const std::shared_ptr<Context>& context, std::unique_ptr<InputOutputLayer> io) :
                context_(std::move(context)), io_(std::move(io)){}

              virtual ~StateMachine() = default;

 public:
  virtual void Execute() = 0;

 protected:
  std::shared_ptr<Context> context_;
  std::unique_ptr<InputOutputLayer> io_;
};

#endif //TASKMANAGER_CLI_STATESCONTROLLERS_STATEMACHINE_H_
