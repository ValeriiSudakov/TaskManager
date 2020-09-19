//
// Created by valeriisudakov on 25.08.20.
//

#include "InputOutputConsoleLayer.h"
#include "ShowByIDState.h"
#include "Factory/Factory.h"
ShowByIDState::ShowByIDState():State(StatesID::SHOW_BY_ID){}

ShowByIDState::~ShowByIDState() = default;

StateOperationResult ShowByIDState::Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) {
  auto inputIDStateMachine = Factory::CreateFiniteStatesMachine( FiniteStateMachineID::INPUT_ID,
                                                                   context,
                                                                   io);
  inputIDStateMachine->Execute();
  auto task = context->taskService_.GetTask(context->buffer_.id);

  if (task.has_value()){
    std::cout<<task.value().ToString()<<std::endl;

    auto subtasks = context->taskService_.GetSubtask(context->buffer_.id);
    if (!subtasks.empty()){
      std::cout<<"Subtasks:\n";
      for (const auto& sub : subtasks){
        std::string taskStr { "* " + sub.GetName() + "\n" };
       io.Output(taskStr);
      }
    }

    return StateOperationResult::SUCCESS;
  }
  std::string notFound { "Task was not found.\n" };
 io.Output(notFound);
  return StateOperationResult::TASKS_LIST_EMPTY;
}
