//
// Created by valeriisudakov on 20.08.20.
//

#include "CompleteState.h"
#include "States/Menus/Menu.h"
#include "Factory/Factory.h"
CompleteState::CompleteState() : State(StatesID::Complete) {}

CompleteState::~CompleteState() = default;

StateOperationResult CompleteState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO) {
  std::unique_ptr<StateMachine> inputIDStateMachine = std::make_unique<FiniteStateMachine>(
                                                  std::list<StatesID>{
                                                          StatesID::InputID,
                                                          StatesID::Exit
                                                  },
                                                  context,
                                                  std::move(std::make_unique<IO_Layer>())
                                              );
  inputIDStateMachine->Execute();
  auto result = context->taskService_->SetTaskComplete(context->buffer_.id);
  if (result){
    std::string success { "Task was completed.\n" };
    IO.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Error.\n" };
    IO.Output(fail);
    return StateOperationResult::FAIL;
  }
}
