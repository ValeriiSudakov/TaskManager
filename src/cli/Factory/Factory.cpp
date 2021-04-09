//
// Created by valeriisudakov on 13.09.20.
//

#include "Factory.h"

#include "StateMachine.h"
#include "FactoryExecuteStatesMachine.h"
#include "FactoryStates.h"

static const auto statesMachineFactory = std::make_unique<FactoryExecuteStatesMachine>();

std::shared_ptr<State> Factory::CreateState(const StatesID &id) {
  static const auto statesFactory = std::make_unique<FactoryStates>();
  return statesFactory->Create(id);
}



std::shared_ptr<StateMachine> Factory::CreateFiniteStatesMachine(const FiniteStateMachineID &id,
                                                                 const std::shared_ptr<Context> &context,
                                                                 InputOutputLayer& io) {

  return statesMachineFactory->Create(id, context, io);
}

std::shared_ptr<StateMachine> Factory::CreateMenuStateMachine(const StatesID &id,
                                                              const std::shared_ptr<Context> &context,
                                                              InputOutputLayer& io) {

  return statesMachineFactory->CreateMenu(id, context, io);


}


std::shared_ptr<StateMachine> Factory::CreateAfterMenuState(const StatesID& stateID,
                                                            const std::shared_ptr<Context>& context,
                                                            InputOutputLayer& io){

  return statesMachineFactory->CreateAfterMenuStatesMachine(stateID, context, io);
}

