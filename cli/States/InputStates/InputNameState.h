//
// Created by valeriisudakov on 21.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTNAMESTATE_H_
#define TASKMANAGER_CLI_STATES_INPUTNAMESTATE_H_
#include "States/State.h"

class InputNameState : public State{
 public:
  InputNameState(std::shared_ptr<State> nextState);
  ~InputNameState();

 public:
  void                      Do(Context& context) override;
  std::shared_ptr<State>    ReadAction() override;
 private:
  std::shared_ptr<State>    nextState_;
  bool                      fail;
};

#endif //TASKMANAGER_CLI_STATES_INPUTNAMESTATE_H_
