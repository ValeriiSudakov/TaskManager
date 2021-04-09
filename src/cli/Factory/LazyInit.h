//
// Created by valeriisudakov on 11.09.20.
//

#include "State.h"

#ifndef TASKMANAGER_CLI_FACTORY_LASYINIT_H_
#define TASKMANAGER_CLI_FACTORY_LASYINIT_H_

class LazyInit{
 public:
  virtual std::shared_ptr<State> Create() = 0;
  virtual ~LazyInit() = default;
};

#endif //TASKMANAGER_CLI_FACTORY_LASYINIT_H_
