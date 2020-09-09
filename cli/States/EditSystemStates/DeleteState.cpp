//
// Created by valeriisudakov on 20.08.20.
//

#include "DeleteState.h"
#include "States/Menu.h"
#include "Factory/Factory.h"
DeleteState::DeleteState() : State(StatesID::Delete){}

DeleteState::~DeleteState() = default;

StateOperationResult DeleteState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) {
  std::unique_ptr<StateMachine> inputIDStateMachine = std::make_unique<FiniteStateMachine>(
                                                    std::list<StatesID>{
                                                        StatesID::ShowAll,
                                                        StatesID::InputID,
                                                        StatesID::Exit
                                                    },
                                                    context,
                                                    std::move(std::make_unique<IO_Layer>())
                                                );
  inputIDStateMachine->Execute();
  auto result = context->taskService_->RemoveTask(context->buffer_.id);
  if (result){
    std::string success { "Task was removed.\n" };
    IO.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Task was not found.\n" };
    IO.Output(fail);
    return StateOperationResult::FAIL;
  }
}

std::shared_ptr<State> DeleteState::ReadAction() {
  return Factory::CreateState(StatesID::Menu);
}
