//
// Created by valeriisudakov on 10.09.20.
//

#ifndef TASKMANAGER_CLI_STATES_EDITSYSTEMSTATES_EDITSTATE_H_
#define TASKMANAGER_CLI_STATES_EDITSYSTEMSTATES_EDITSTATE_H_
#include "States/State.h"

class EditState : public State{
 public:
  EditState(StatesID editStateID) : State (StatesID::Edit), editStateID_(editStateID){}
  ~EditState() = default;

  StateOperationResult    Do(const std::shared_ptr<Context> &context, const InputOutputLayer& io) override;
  std::shared_ptr<State>  ReadAction() override;

 private:
  StatesID editStateID_;
};


#endif //TASKMANAGER_CLI_STATES_EDITSYSTEMSTATES_EDITSTATE_H_
