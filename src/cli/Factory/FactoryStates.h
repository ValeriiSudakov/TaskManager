//
// Created by valeriisudakov on 11.09.20.
//

#ifndef TASKMANAGER_CLI_FACTORY_FACTORYSTATES_H_
#define TASKMANAGER_CLI_FACTORY_FACTORYSTATES_H_
#include <map>
#include "State.h"
#include "LazyInit.h"

class FactoryStates {
 public:
  FactoryStates();

 public:
  std::shared_ptr<State> Create(StatesID id);

 private:
  std::map<StatesID, std::shared_ptr<State>> menuStates_;
  std::map<StatesID, std::unique_ptr<LazyInit>> states_;
};

std::shared_ptr<State> CreateMenu(StatesID id);
std::shared_ptr<State> CreateState(StatesID id);


#endif //TASKMANAGER_CLI_FACTORY_FACTORYSTATES_H_
