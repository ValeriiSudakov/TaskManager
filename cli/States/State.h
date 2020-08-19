//
// Created by valeriisudakov on 18.08.20.
//

#ifndef TASKMANAGER_CLI_STATE_H_
#define TASKMANAGER_CLI_STATE_H_
#include "Context.h"
#include <iostream>

class State {
 public:
  virtual ~State();

 public:
  virtual void      Do() = 0;
  virtual void      PrintActions() = 0;
  virtual void      ReadAction() = 0;

          void      SetContext(std::shared_ptr<Context> context);
          void      PrintState();
 protected:
  std::string stateName_;
  std::shared_ptr<Context> context_;
};

#endif //TASKMANAGER_CLI_STATE_H_
