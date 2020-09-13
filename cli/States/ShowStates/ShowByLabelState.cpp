//
// Created by valeriisudakov on 20.08.20.
//

#include "ShowByLabelState.h"
#include "Factory/Factory.h"
#include "InputOutputConsoleLayer.h"

ShowByLabelState::ShowByLabelState() : State(StatesID::SHOW_BY_LABEL){}

ShowByLabelState::~ShowByLabelState() = default;

StateOperationResult ShowByLabelState::Do(const std::shared_ptr<Context>& context, const InputOutputLayer& IO) {
  auto inputLabelMachine = Factory::CreateFiniteStatesMachine( FiniteStateMachineID::INPUT_LABEL,
                                                               context,
                                                               std::move(std::make_unique<InputOutputConsoleLayer>()));
  inputLabelMachine->Execute();

  auto task = context->taskService_->GetTask(context->buffer_.id);

  std::string output { "Tasks list will be updated. Sort tasks by priority? [y/n]: " };
  IO.Output(output);
  std::string inputSort { IO.Input()};

  if (inputSort == "y") {
    context->tasks_ = context->taskService_->GetTasksByLabel(context->buffer_.label, true);
  } else if (inputSort == "n") {
    context->tasks_ = context->taskService_->GetTasksByLabel(context->buffer_.label, false);
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

