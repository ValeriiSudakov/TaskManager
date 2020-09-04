//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowThisWeekState.h"
#include "States/BaseState.h"
#include "Factory/Factory.h"

ShowThisWeekState::ShowThisWeekState() : State(StatesID::ShowThisWeek) {}

ShowThisWeekState::~ShowThisWeekState() = default;

StateOperationResult ShowThisWeekState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) {

  std::string output { "Tasks list will be updated. Sort tasks by priority? [y/n]: " };
  IO.Output(output);
  std::string inputSort { IO.Input()};

  if (inputSort == "y") {
    context->tasks_ = context->taskService_->GetWeekTasks(true);
  } else if (inputSort == "n") {
    context->tasks_ = context->taskService_->GetWeekTasks(false);
  } else {
    std::string error { "Incorrect input.\n" };
    IO.Output(error);
    return StateOperationResult::INCORRECT_INPUT;
  }
  if (context->tasks_.empty()){
    std::string notFound { "Tasks were not found.\n" };
    IO.Output(notFound);
    return StateOperationResult::TASKS_LIST_EMPTY;
  }
  int taskNumber = 0;
  for (const auto& task : context->tasks_){
    std::string taskStr { std::to_string(taskNumber++) + ": " + task.GetName() + "\n" };
    IO.Output(taskStr);
  }
  return StateOperationResult::SUCCESS;
}

std::shared_ptr<State> ShowThisWeekState::ReadAction() {
  return Factory::CreateState(StatesID::Base);
}
