//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowAllState.h"

ShowAllState::ShowAllState() : State( StatesID::SHOW_ALL){}

ShowAllState::~ShowAllState() = default;

StateOperationResult ShowAllState::Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) {
  std::string output { "Tasks list will be updated. Sort tasks by priority? [y/n]: " };
  io.Output(output);
  std::string inputSort { io.Input()};
  context->tasks_.clear();
  if (inputSort == "y") {
    context->tasks_ = context->taskService_->GetTasks(true);
  } else if (inputSort == "n") {
    context->tasks_ = context->taskService_->GetTasks(false);
  } else {
    std::string error { "Incorrect input.\n" };
    io.Output(error);
    return StateOperationResult::INCORRECT_INPUT;
  }
  if (context->tasks_.empty()){
    std::string notFound { "Tasks were not found.\n" };
    io.Output(notFound);
    return StateOperationResult::TASKS_LIST_EMPTY;
  }
  int taskNumber = 0;
  for (const auto& task : context->tasks_){
    std::string taskStr { std::to_string(taskNumber++) + ": " + task.GetName() + "\n" };
    io.Output(taskStr);
  }



  return StateOperationResult::SUCCESS;
}
