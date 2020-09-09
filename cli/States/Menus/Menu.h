//
// Created by valeriisudakov on 09.09.20.
//

#ifndef TASKMANAGER_CLI_STATES_MENUS_MENU_H_
#define TASKMANAGER_CLI_STATES_MENUS_MENU_H_
#include "States/State.h"

class Menu : public State {
 public:
  Menu(StatesID id) : State(id) { }
  virtual ~Menu() = default;

 public:
  virtual StateOperationResult              Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) override;
  virtual std::shared_ptr<State>            ReadAction() override;

 protected:
  void                                      PrintNextStates(const IO_LayerInterface& io) const;

 protected:
  std::map<std::string, StatesID>   actions_;
};
#endif //TASKMANAGER_CLI_STATES_MENUS_MENU_H_
