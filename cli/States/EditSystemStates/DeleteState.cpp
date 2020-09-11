//
// Created by valeriisudakov on 20.08.20.
//

#include "DeleteState.h"
#include "States/Menus/Menu.h"
#include "Factory/Factory.h"
DeleteState::DeleteState() : State(StatesID::Delete){}

DeleteState::~DeleteState() = default;

StateOperationResult DeleteState::Do(const std::shared_ptr<Context>& context, const InputOutputLayer& io) {
  std::unique_ptr<StateMachine> inputIDStateMachine = std::make_unique<FiniteStateMachine>(
                                                    std::list<StatesID>{
                                                        StatesID::InputID,
                                                        StatesID::Exit
                                                    },
                                                    context,
                                                    std::move(std::make_unique<InputOutpuConsoleLayer>())
                                                );
  inputIDStateMachine->Execute();
  auto result = context->taskService_->RemoveTask(context->buffer_.id);
  if (result){
    std::string success { "Task was removed.\n" };
    io.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Task was not found.\n" };
    io.Output(fail);
    return StateOperationResult::FAIL;
  }
}

