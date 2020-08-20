//
// Created by valeriisudakov on 19.08.20.
//

#ifndef TASKMANAGER_CLI_STATES_STATESFACTORY_H_
#define TASKMANAGER_CLI_STATES_STATESFACTORY_H_
#include <memory>
#include "State.h"
#include "BaseState.h"
#include "AddTaskState.h"
#include "AddSubtaskState.h"
#include "CompleteState.h"
#include "DeleteState.h"
#include "PostponeState.h"
#include "ShowAllState.h"
#include "ShowByLabelState.h"
#include "ShowByNameState.h"
#include "ShowThisWeekState.h"
#include "ShowTodayState.h"

namespace StatesFactory{
  static std::unique_ptr<State> Create(std::string input){
    if (input == "base state"){
      return std::make_unique<BaseState>();
    }
    if (input == "add task"){
      return std::make_unique<AddTaskState>();
    }
    if (input == "add subtask"){
      return std::make_unique<AddSubtaskState>();
    }
    if (input == "complete"){
      return std::make_unique<CompleteState>();
    }
    if (input == "delete"){
      return std::make_unique<DeleteState>();
    }
    if (input == "postpone"){
      return std::make_unique<PostponeState>();
    }
    if (input == "show all"){
      return std::make_unique<ShowAllState>();
    }
    if (input == "show by label"){
      return std::make_unique<ShowByLabelState>();
    }
    if (input == "show by name"){
      return std::make_unique<ShowByNameState>();
    }
    if (input == "show this week"){
      return std::make_unique<ShowThisWeekState>();
    }
    if (input == "show today"){
      return std::make_unique<ShowTodayState>();
    }
    if (input == "exit"){
      return nullptr;
    }
    return std::make_unique<BaseState>();
  }
}
#endif //TASKMANAGER_CLI_STATES_STATESFACTORY_H_
