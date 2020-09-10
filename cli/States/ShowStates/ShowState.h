//
// Created by valeriisudakov on 09.09.20.
//

#ifndef TASKMANAGER_CLI_STATES_SHOWSTATES_SHOWSTATE_H_
#define TASKMANAGER_CLI_STATES_SHOWSTATES_SHOWSTATE_H_
#include "States/State.h"

class ShowState : public State{
 public:
  ShowState(StatesID showStateID) : State (StatesID::Show), showStateID_(showStateID){}
  ~ShowState() = default;

  StateOperationResult    Do(const std::shared_ptr<Context> &context, const IO_LayerInterface &IO) override;
  std::shared_ptr<State>  ReadAction() override;
 private:
  StatesID showStateID_;
};

#endif //TASKMANAGER_CLI_STATES_SHOWSTATES_SHOWSTATE_H_
