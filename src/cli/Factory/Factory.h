//
// Created by valeriisudakov on 13.09.20.
//

#ifndef TASKMANAGER_CLI_FACTORY_FACTORY_H_
#define TASKMANAGER_CLI_FACTORY_FACTORY_H_

#include "FiniteStatesMachinesList.h"
#include "StatesID.h"
#include <memory>
#include "State.h"
#include "StateMachine.h"

class Context;
class InputOutputLayer;

class Factory{
 public:
  static std::shared_ptr<State>        CreateState(const StatesID& id);
  static std::shared_ptr<StateMachine> CreateFiniteStatesMachine(const FiniteStateMachineID& id,
                                                                 const std::shared_ptr<Context>& context,
                                                                 InputOutputLayer& io);

  static std::shared_ptr<StateMachine> CreateMenuStateMachine(const StatesID &id,
                                                              const std::shared_ptr<Context> &context,
                                                              InputOutputLayer& io);

  static std::shared_ptr<StateMachine> CreateAfterMenuState(const StatesID& stateID,
                                                            const std::shared_ptr<Context>& context,
                                                            InputOutputLayer& io);

};


#endif //TASKMANAGER_CLI_FACTORY_FACTORY_H_
