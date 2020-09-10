//
// Created by valeriisudakov on 20.08.20.
//

#include "StatesControllers/StateMachineMenu.h"
#include "ShowTodayState.h"
#include "States/Menus/Menu.h"
#include "Factory/Factory.h"

ShowTodayState::ShowTodayState() : State(StatesID::ShowToday) {}

ShowTodayState::~ShowTodayState() = default;


StateOperationResult ShowTodayState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) {

  std::string output { "Tasks list will be updated. Sort tasks by priority? [y/n]: " };
  IO.Output(output);
  std::string inputSort { IO.Input()};

  if (inputSort == "y") {
    context->tasks_ = context->taskService_->GetTodayTasks(true);
  } else if (inputSort == "n") {
    context->tasks_ = context->taskService_->GetTodayTasks(false);
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

