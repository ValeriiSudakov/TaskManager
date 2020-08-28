//
// Created by valeriisudakov on 18.08.20.
//

#ifndef TASKMANAGER_CLI_STATE_H_
#define TASKMANAGER_CLI_STATE_H_
#include <set>
#include <iostream>
#include <memory>
#include "Context.h"
#include "StateOperationResult.h"
#include "StatesID.h"

class State {
 public:

  virtual ~State();

 public:
  virtual void                        PrintNextStates();
  virtual std::shared_ptr<State>      ReadAction();
  virtual StateOperationResult        Do(const std::shared_ptr<Context>& context) = 0;
  StatesID                            GetStateID() const { return stateID_; }

 protected:
  StatesID stateID_;
};

#endif //TASKMANAGER_CLI_STATE_H_
