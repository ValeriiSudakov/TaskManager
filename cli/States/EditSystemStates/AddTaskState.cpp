//
// Created by valeriisudakov on 18.08.20.
//

#include "AddTaskState.h"
#include "States/BaseState.h"

AddTaskState::AddTaskState() {
  stateName_ = "add task";
}

AddTaskState::~AddTaskState() = default;

void AddTaskState::Do(Context& context){
  auto result = context.taskService_->AddTask(TaskDTO::Create(context.buffer_.name, context.buffer_.label,
                                                context.buffer_.priority, context.buffer_.date));
  std::cout<<(result.success_ ? "Task was added.\n" : "Error.\n");
}

std::shared_ptr<State> AddTaskState::ReadAction() {
  return std::make_shared<BaseState>();
}