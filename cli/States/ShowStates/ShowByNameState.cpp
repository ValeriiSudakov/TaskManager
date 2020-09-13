//
// Created by valeriisudakov on 20.08.20.
//
#include "InputOutpuConsoleLayer.h"
#include "ShowByNameState.h"
#include "Factory/Factory.h"
ShowByNameState::ShowByNameState() : State (StatesID::SHOW_BY_NAME) {}

ShowByNameState::~ShowByNameState() = default;

StateOperationResult ShowByNameState::Do(const std::shared_ptr<Context>& context, const InputOutputLayer& IO) {
  auto inputNameStateMachine = Factory::CreateFiniteStatesMachine( FiniteStateMachineID::INPUT_NAME,
                                                                 context,
                                                                 std::move(std::make_unique<InputOutpuConsoleLayer>()));
  inputNameStateMachine->Execute();

  std::string output { "Tasks list will be updated. Sort tasks by priority? [y/n]: " };
  IO.Output(output);
  std::string inputSort { IO.Input()};

  if (inputSort == "y") {
    context->tasks_ = context->taskService_->GetTasksByName(context->buffer_.name, true);
  } else if (inputSort == "n") {
    context->tasks_ = context->taskService_->GetTasksByName(context->buffer_.name, false);
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
