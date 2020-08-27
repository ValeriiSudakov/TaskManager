//
// Created by valeriisudakov on 20.08.20.
//

#include "AddSubtaskState.h"
#include "States/BaseState.h"
#include "Factory.h"

AddSubtaskState::AddSubtaskState() {
  stateName_ = "add subtask";
}

AddSubtaskState::~AddSubtaskState() = default;

void AddSubtaskState::Do(const std::shared_ptr<Context>& context) {
  auto result = context->taskService_->AddSubtask(context->buffer_.id,
                                                 TaskDTO::Create(context->buffer_.name, context->buffer_.label,
                                                                 context->buffer_.priority, context->buffer_.date));

  std::cout<<(result.success_ ? "Subtask was added.\n" : "Error.\n");
}

std::shared_ptr<State> AddSubtaskState::ReadAction() {
  return Factory::CreateState(StatesList::Base);
}
