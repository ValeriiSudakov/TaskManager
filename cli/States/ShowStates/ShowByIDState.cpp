//
// Created by valeriisudakov on 25.08.20.
//

#include "ShowByIDState.h"
#include "States/Menu.h"
#include "Factory/Factory.h"
ShowByIDState::ShowByIDState():State(StatesID::ShowByID){}

ShowByIDState::~ShowByIDState() = default;

StateOperationResult ShowByIDState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) {
  auto chooseIDMachine = Factory::CreateStateMachine(FiniteStateMachinesList::ChooseID, context);
  chooseIDMachine->Execute();
  auto task = context->taskService_->GetTask(context->buffer_.id);
  if (task.has_value()){
    std::cout<<task.value().ToString()<<std::endl;

    auto subtasks = context->taskService_->GetSubtask(context->buffer_.id);
    if (!subtasks.empty()){
      std::cout<<"Subtasks:\n";
      for (const auto& sub : subtasks){
        std::string taskStr { "* " + sub.GetName() + "\n" };
        IO.Output(taskStr);
      }
    }

    return StateOperationResult::SUCCESS;
  }
  std::string notFound { "Task was not found.\n" };
  IO.Output(notFound);
  return StateOperationResult::TASKS_LIST_EMPTY;
}

std::shared_ptr<State> ShowByIDState::ReadAction() {
  return Factory::CreateState(StatesID::Menu);
}