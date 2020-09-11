//
// Created by valeriisudakov on 11.09.20.
//

#ifndef TASKMANAGER_CLI_FACTORY_LASYINITCLASS_H_
#define TASKMANAGER_CLI_FACTORY_LASYINITCLASS_H_
#include "LasyInit.h"

template <typename StateClass>
class LasyInitClass : public LasyInit{
 public:
  LasyInitClass() : state_(nullptr) { }
  ~LasyInitClass() = default;

 public:
  std::shared_ptr<State> Create() override {
    return (state_ ? state_ : (state_ = std::make_shared<StateClass>()) );
  }

 private:
  std::shared_ptr<State> state_;
};

#endif //TASKMANAGER_CLI_FACTORY_LASYINITCLASS_H_
