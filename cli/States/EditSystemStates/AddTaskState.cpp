//
// Created by valeriisudakov on 18.08.20.
//

#include "AddTaskState.h"
#include "States/Menus/BaseMenu.h"
#include "Factory/Factory.h"

AddTaskState::AddTaskState() : State(StatesID::AddTask){}

AddTaskState::~AddTaskState() = default;

StateOperationResult AddTaskState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) {
  std::unique_ptr<StateMachine> addTaskMachine = std::make_unique<FiniteStateMachine>(
                                          std::list<StatesID>{
                                                    StatesID::InputTask,
                                                    StatesID::Exit
                                                },
                                                context,
                                                std::move(std::make_unique<IO_Layer>())
                                          );

  addTaskMachine->Execute();
  auto result = context->taskService_->AddTask(TaskDTO::Create(context->buffer_.name, context->buffer_.label,
                                                context->buffer_.priority, context->buffer_.date));

  if (result.success_){
    std::string success {"Task was added.\n"};
    IO.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Failed.\n" };
    return StateOperationResult::FAIL;
  }
}

std::shared_ptr<State> AddTaskState::ReadAction() {
  return Factory::CreateState(StatesID::BaseMenu);
}