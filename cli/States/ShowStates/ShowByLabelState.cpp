//
// Created by valeriisudakov on 20.08.20.
//

#include "StatesControllers/StateMachineMenu.h"
#include "ShowByLabelState.h"
#include "States/Menus/BaseMenu.h"
#include "Factory/Factory.h"

ShowByLabelState::ShowByLabelState() : State(StatesID::ShowByLabel){}

ShowByLabelState::~ShowByLabelState() = default;

StateOperationResult ShowByLabelState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) {
  std::unique_ptr<StateMachine> inputLabelDStateMachine = std::make_unique<FiniteStateMachine>(
      std::list<StatesID>{
          StatesID::InputLabel,
          StatesID::Exit
      },
      context,
      std::move(std::make_unique<IO_Layer>())
  );
  inputLabelDStateMachine->Execute();

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

std::shared_ptr<State> ShowByLabelState::ReadAction() {
  return Factory::CreateState(StatesID::BaseMenu);
}
