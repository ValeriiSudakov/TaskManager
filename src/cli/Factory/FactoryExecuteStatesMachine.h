//
// Created by valeriisudakov on 13.09.20.
//

#ifndef TASKMANAGER_CLI_FACTORY_FACTORYEXECUTESTATESMACHINE_H_
#define TASKMANAGER_CLI_FACTORY_FACTORYEXECUTESTATESMACHINE_H_
#include "StateMachine.h"
#include "FiniteStatesMachinesList.h"
#include <map>

class FactoryExecuteStatesMachine {
 public:
  FactoryExecuteStatesMachine();
  ~FactoryExecuteStatesMachine();

 public:
  std::shared_ptr<StateMachine> Create(const FiniteStateMachineID& id,
                                       const std::shared_ptr<Context>& context,
                                             InputOutputLayer& io);

  std::shared_ptr<StateMachine> CreateAfterMenuStatesMachine(const StatesID& stateID,
                                                             const std::shared_ptr<Context>& context,
                                                             InputOutputLayer& io);


  std::shared_ptr<StateMachine> CreateMenu(const StatesID& id,
                                           const std::shared_ptr<Context>& context,
                                           InputOutputLayer& io);


 private:
  std::map<FiniteStateMachineID, std::shared_ptr<StateMachine>> stateMachines_;
};

#endif //TASKMANAGER_CLI_FACTORY_FACTORYEXECUTESTATESMACHINE_H_
