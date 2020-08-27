//
// Created by valeriisudakov on 20.08.20.
//

#include "DeleteState.h"
#include "States/BaseState.h"
#include "Factory.h"
DeleteState::DeleteState(){
  stateName_ = "delete";
}

DeleteState::~DeleteState() = default;

void DeleteState::Do(const std::shared_ptr<Context>& context) {
  auto result = context->taskService_->RemoveTask(context->buffer_.id);
  std::cout<< (result ? "Task was removed.\n" : "task was not found.\n");
}

std::shared_ptr<State> DeleteState::ReadAction() {
  return Factory::CreateState(StatesList::Base);
}
