//
// Created by valeriisudakov on 09.09.20.
//

#ifndef TASKMANAGER_CLI_STATES_MENUS_MENU_H_
#define TASKMANAGER_CLI_STATES_MENUS_MENU_H_
#include "States/State.h"
#include "MenuActions.h"

class Menu : public State {
 public:
  Menu(StatesID id, std::unique_ptr<Actions> actions) : State(id), actions_(std::move(actions)) { }
  virtual ~Menu() = default;

 public:
  virtual StateOperationResult              Do(const std::shared_ptr<Context>& context, std::shared_ptr<InputOutputLayer> io) override;
  virtual std::shared_ptr<State>            ReadAction(std::shared_ptr<InputOutputLayer> io) override;

 private:
  void                                      PrintNextStates(std::shared_ptr<InputOutputLayer> io) const;

 private:
  std::unique_ptr<Actions> actions_;
};
#endif //TASKMANAGER_CLI_STATES_MENUS_MENU_H_
