//
// Created by valeriisudakov on 18.08.20.
//

#ifndef TASKMANAGER_CLI_STATE_H_
#define TASKMANAGER_CLI_STATE_H_
#include <set>
#include <iostream>
#include <memory>
#include "Context.h"

class State {
 public:
  virtual ~State();

 public:
  virtual void                        Do(Context& context) = 0;
  virtual void                        PrintNextStates();
  virtual std::shared_ptr<State>      ReadAction();
  void                                PrintState();

 protected:
  std::string                 stateName_;
};

#endif //TASKMANAGER_CLI_STATE_H_
