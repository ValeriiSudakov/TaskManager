//
// Created by valeriisudakov on 25.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTIDSTATE_H_
#define TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTIDSTATE_H_
#include "States/State.h"

class InputIDState : public State {
 public:
  InputIDState(std::shared_ptr<State> nextState);
  ~InputIDState();

 public:
  void                        Do(Context& context) override;
  std::shared_ptr<State>      ReadAction() override;

 private:
  std::shared_ptr<State>      nextState_;
  bool                        fail;
};

#endif //TASKMANAGER_CLI_STATES_INPUTSTATES_INPUTIDSTATE_H_
