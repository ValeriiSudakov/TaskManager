//
// Created by valeriisudakov on 20.08.20.
//

#include "PostponeState.h"
#include "States/BaseState.h"
#include "Factory.h"
PostponeState::PostponeState() {
  stateName_ = "postpone";
}

PostponeState::~PostponeState() = default;

void PostponeState::Do(const std::shared_ptr<Context>& context) {
  auto result = context->taskService_->PostponeTask(context->buffer_.id, context->buffer_.date);
  std::cout<<(result ? "Task postponed successfully.\n" : "Postpone failed.\n");
}

std::shared_ptr<State> PostponeState::ReadAction() {
  return Factory::CreateState(StatesList::Base);
}