//
// Created by valeriisudakov on 11.09.20.
//

#ifndef TASKMANAGER_CLI_FACTORY_LAZYINITCLASS_H_
#define TASKMANAGER_CLI_FACTORY_LAZYINITCLASS_H_
#include "LazyInit.h"

template <typename StateClass>
class LazyInitClass : public LazyInit{
 public:
  LazyInitClass() : state_(nullptr) { }
  ~LazyInitClass() = default;

 public:
  std::shared_ptr<State> Create() override {
    return (state_ ? state_ : (state_ = std::make_shared<StateClass>()) );
  }

 private:
  std::shared_ptr<State> state_;
};

#endif //TASKMANAGER_CLI_FACTORY_LAZYINITCLASS_H_
