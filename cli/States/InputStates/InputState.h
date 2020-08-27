//
// Created by valeriisudakov on 27.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTSTATE_H_
#define TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTSTATE_H_
#include "Context.h"
class InputState {
 public:
  virtual ~InputState() = default;

 public:
  virtual bool Do(const std::shared_ptr<Context>& context) = 0;
};

#endif //TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTSTATE_H_
