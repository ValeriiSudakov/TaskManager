//
// Created by valeriisudakov on 18.08.20.
//

#ifndef TASKMANAGER_CLI_CONTEXT_H_
#define TASKMANAGER_CLI_CONTEXT_H_
#include "API/TaskService.h"
#include "States/State.h"

class Context {
 public:
  Context(std::shared_ptr<State> state);
  ~Context();

  void Request();

  void TransitionTo(std::shared_ptr<State> state);
 private:
  std::shared_ptr<TaskService> taskService_;
  std::shared_ptr<State> state_;
};

#endif //TASKMANAGER_CLI_CONTEXT_H_
