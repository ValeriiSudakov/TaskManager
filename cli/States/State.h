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
  virtual void                Do(Context& context) = 0;
          void                PrintNextStates_();
          void                PrintState();
  std::unique_ptr<State>      ReadAction();

 protected:
  std::string                 stateName_;
  std::set<std::string>       nextStates_;
};

#endif //TASKMANAGER_CLI_STATE_H_
