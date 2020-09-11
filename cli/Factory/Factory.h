//
// Created by valeriisudakov on 27.08.20.
//

#ifndef TASKMANAGER_CLI_FACTORY_H_
#define TASKMANAGER_CLI_FACTORY_H_

#include "StatesControllers/StateMachine.h"
#include "StatesControllers/FiniteStateMachine.h"
#include "InputOutpuConsoleLayer.h"
#include "FactoryStates.h"

namespace Factory {

  static std::shared_ptr<State> CreateState(const StatesID& id) {
    static const auto statesFactory = std::make_unique<FactoryStates>();
    return statesFactory->Create(id);
  }
};


#endif //TASKMANAGER_CLI_FACTORY_H_
