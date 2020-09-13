//
// Created by valeriisudakov on 13.09.20.
//

#ifndef TASKMANAGER_CLI_FACTORY_FACTORYFINITESTATESMACHINES_H_
#define TASKMANAGER_CLI_FACTORY_FACTORYFINITESTATESMACHINES_H_
#include "StatesControllers/StateMachine.h"
#include "StatesControllers/FiniteStatesMachinesList.h"
#include <set>

class FactoryFiniteStatesMachines {
 public:
  FactoryFiniteStatesMachines();
  ~FactoryFiniteStatesMachines();

 public:
  std::shared_ptr<StateMachine> Create(const FiniteStateMachineID& id,
                                       const std::shared_ptr<Context>& context,
                                             std::unique_ptr<InputOutputLayer> io);

  std::shared_ptr<StateMachine> CreateAfterMenuState(const StatesID& stateID,
                                                     const std::shared_ptr<Context>& context,
                                                     std::unique_ptr<InputOutputLayer> io);


  std::shared_ptr<StateMachine> CreateMenu(const StatesID& id,
                                           const std::shared_ptr<Context>& context,
                                           std::unique_ptr<InputOutputLayer> io);


 private:
  std::map<FiniteStateMachineID, std::shared_ptr<StateMachine>> stateMachines_;
};

#endif //TASKMANAGER_CLI_FACTORY_FACTORYFINITESTATESMACHINES_H_
