//
// Created by valeriisudakov on 20.08.20.
//
#include "Context.h"

Context::Context() {
  taskService_ = std::make_unique<TaskService>(TaskService::Create());
}