//
// Created by valeriisudakov on 18.08.20.
//

#ifndef TASKMANAGER_CLI_STATE_H_
#define TASKMANAGER_CLI_STATE_H_

#include <memory>
#include "Context.h"
#include "StateOperationResult.h"
#include "StatesID.h"
#include "InputOutputLayer.h"

class State {
 public:
  State(StatesID stateID) : stateID_(stateID){ }
  virtual ~State() = default;

 public:
  virtual std::shared_ptr<State>      ReadAction() { }
  virtual StateOperationResult        Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) = 0;
  StatesID                            GetStateID() const { return stateID_; }

 private:
  StatesID stateID_;
};

#endif //TASKMANAGER_CLI_STATE_H_
