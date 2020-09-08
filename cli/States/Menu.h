//
// Created by valeriisudakov on 18.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_BASESTATE_H_
#define TASKMANAGER_CLI_STATES_BASESTATE_H_
#include "State.h"

class State;

class Menu : public State {
 public:
  Menu();
  ~Menu();

 public:
  StateOperationResult              Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) override;
  std::shared_ptr<State>            ReadAction() override;

private:
  void                              PrintNextStates(const IO_LayerInterface& io) const;

private:
  std::map<std::string, StatesID>   actions_;
};

#endif //TASKMANAGER_CLI_STATES_BASESTATE_H_
