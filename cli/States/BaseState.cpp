//
// Created by valeriisudakov on 18.08.20.
//

#include "BaseState.h"
#include "Factory/Factory.h"


BaseState::BaseState() : State(StatesID::Base){ }

BaseState::~BaseState() = default;


StateOperationResult BaseState::Do(const std::shared_ptr<Context>& context, const IO_LayerInterface& IO){
  return StateOperationResult::SUCCESS;
}

void PrintNextStates(const IO_LayerInterface& io) {
  std::string addTask{"add task\n"};
  io.Output(addTask);
  std::string addSubtask{"add subtask\n"};
  io.Output(addSubtask);
  std::string showByID{"show by ID\n"};
  io.Output(showByID);
  std::string showAll{"show all\n"};
  io.Output(showAll);
  std::string showToday{"show today\n"};
  io.Output(showToday);
  std::string showWeek{"show this week\n"};
  io.Output(showWeek);
  std::string showByName{"show by name\n"};
  io.Output(showByName);
  std::string showByLabel{"show by label\n"};
  io.Output(showByLabel);
  std::string postpone{"postpone\n"};
  io.Output(postpone);
  std::string remove{"remove\n"};
  io.Output(remove);
  std::string complete{"complete\n"};
  io.Output(complete);
  std::string exit{"exit\n"};
  io.Output(exit);
}

std::shared_ptr<State> BaseState::ReadAction() {
  IO_Layer io;
  PrintNextStates(io);

  std::string output {"input command: "};
  io.Output(output);

  std::string input { io.Input() };

  if (input == "add task"){
    return std::move(Factory::CreateState(StatesID::AddTask));

  } else if (input == "add subtask") {
    return std::move(Factory::CreateState(StatesID::AddSubtask));

  } else if (input == "show all"){
    return std::move(Factory::CreateState(StatesID::ShowAll));

  } else if (input == "show this week"){
    return std::move(Factory::CreateState(StatesID::ShowThisWeek));

  } else if (input == "show by ID"){
    return std::move(Factory::CreateState(StatesID::ShowByID));

  } else if (input == "show by name"){
    return std::move(Factory::CreateState(StatesID::ShowByName));

  } else if (input == "show today"){
    return std::move(Factory::CreateState(StatesID::ShowToday));

  } else if (input == "show by label"){
    return std::move(Factory::CreateState(StatesID::ShowByLabel));

  } else if (input == "postpone"){
    return std::move(Factory::CreateState(StatesID::Postpone));

  } else if (input == "remove"){
    return std::move(Factory::CreateState(StatesID::Delete));

  } else if (input == "complete") {
    return std::move(Factory::CreateState(StatesID::Complete));

  } else if (input == "exit"){
    return nullptr;
  }
  else {
    return std::move(std::make_shared<BaseState>());
  }
}
