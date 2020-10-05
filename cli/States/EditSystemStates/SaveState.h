//
// Created by valeriisudakov on 05.10.20.
//

#ifndef TASKMANAGER_CLI_STATES_EDITSYSTEMSTATES_SAVESTATE_H_
#define TASKMANAGER_CLI_STATES_EDITSYSTEMSTATES_SAVESTATE_H_
#include "States/State.h"

class SaveState : public State {
 public:
  SaveState();
  ~SaveState();

 public:
  StateOperationResult        Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) override;
};

#endif //TASKMANAGER_CLI_STATES_EDITSYSTEMSTATES_SAVESTATE_H_
