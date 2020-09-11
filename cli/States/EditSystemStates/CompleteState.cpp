//
// Created by valeriisudakov on 20.08.20.
//

#include "CompleteState.h"
#include "States/Menus/Menu.h"
#include "Factory/Factory.h"
CompleteState::CompleteState() : State(StatesID::Complete) {}

CompleteState::~CompleteState() = default;

StateOperationResult CompleteState::Do(const std::shared_ptr<Context>& context, const InputOutputLayer& io) {
  std::unique_ptr<StateMachine> inputIDStateMachine = std::make_unique<FiniteStateMachine>(
                                                  std::list<StatesID>{
                                                          StatesID::InputID,
                                                          StatesID::Exit
                                                  },
                                                  context,
                                                  std::move(std::make_unique<InputOutpuConsoleLayer>())
                                              );
  inputIDStateMachine->Execute();
  auto result = context->taskService_->SetTaskComplete(context->buffer_.id);
  if (result){
    std::string success { "Task was completed.\n" };
    io.Output(success);
    return StateOperationResult::SUCCESS;
  } else {
    std::string fail { "Error.\n" };
    io.Output(fail);
    return StateOperationResult::FAIL;
  }
}
