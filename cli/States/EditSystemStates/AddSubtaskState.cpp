//
// Created by valeriisudakov on 20.08.20.
//

#include "AddSubtaskState.h"
#include "States/Menus/Menu.h"
#include "Factory/Factory.h"

AddSubtaskState::AddSubtaskState() : State(StatesID::AddSubtask){ }

AddSubtaskState::~AddSubtaskState() = default;

StateOperationResult AddSubtaskState::Do(const std::shared_ptr<Context>& context, const InputOutputLayer& io) {
  std::unique_ptr<StateMachine> addTaskMachine = std::make_unique<FiniteStateMachine>(
                                                std::list<StatesID>{
                                                  StatesID::InputID,
                                                  StatesID::InputTask,
                                                  StatesID::Exit
                                                },
                                                context,
                                                std::move(std::make_unique<InputOutpuConsoleLayer>())
                                            );
  addTaskMachine->Execute();

  auto result = context->taskService_->AddSubtask(context->buffer_.id,
                                                 TaskDTO::Create(context->buffer_.name, context->buffer_.label,
                                                                 context->buffer_.priority, context->buffer_.date));

  if (result.success_){
    std::string success {"Subtask was added.\n"} ;
    io.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Failed.\n" };
    io.Output(fail);
    return StateOperationResult::FAIL;
  }
}

