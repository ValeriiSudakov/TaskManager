//
// Created by valeriisudakov on 21.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTLABELSTATE_H_
#define TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTLABELSTATE_H_
#include "States/State.h"


class InputLabelState :  public State{
 public:
  InputLabelState(std::shared_ptr<State> nextState);
  ~InputLabelState();

 public:
  void                      Do(Context& context) override;
  std::shared_ptr<State>    ReadAction() override;

 private:
  std::shared_ptr<State>    nextState_;
  bool                      fail;
};

#endif //TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTLABELSTATE_H_
