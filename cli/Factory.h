//
// Created by valeriisudakov on 27.08.20.
//

#ifndef TASKMANAGER_CLI_FACTORY_H_
#define TASKMANAGER_CLI_FACTORY_H_
#include "StatesControllers/FiniteStateMachine.h"
#include "StatesControllers/FiniteStateMachinesList.h"
#include "States/StatesList.h"
#include "States/EditSystemStates/AddTaskState.h"
#include "States/EditSystemStates/AddSubtaskState.h"
#include "States/EditSystemStates/CompleteState.h"
#include "States/EditSystemStates/DeleteState.h"
#include "States/EditSystemStates/PostponeState.h"

#include "States/InputStates/InputNameState.h"
#include "States/InputStates/InputLabelState.h"
#include "States/InputStates/InputPriorityState.h"
#include "States/InputStates/InputDateState.h"
#include "States/InputStates/InputIDState.h"
#include "States/InputStates/InputState.h"

#include "States/ShowStates/ShowAllState.h"
#include "States/ShowStates/ShowTodayState.h"
#include "States/ShowStates/ShowThisWeekState.h"
#include "States/ShowStates/ShowByNameState.h"
#include "States/ShowStates/ShowByLabelState.h"
#include "States/ShowStates/ShowByIDState.h"
#include "States/BaseState.h"
#include <vector>

namespace Factory {
  static FiniteStateMachine CreateStateMachine(const FiniteStateMachinesList &stateMachine,
                                               const std::shared_ptr<Context>& context) {
    if (stateMachine == FiniteStateMachinesList::AddTask) {
      std::vector<InputStatesList> states{InputStatesList::InputName, InputStatesList::InputLabel,
                                          InputStatesList::InputPriority, InputStatesList::InputDate};
      return FiniteStateMachine(states, context);
    }
    if (stateMachine == FiniteStateMachinesList::AddSubtask) {
      std::vector<InputStatesList> states{InputStatesList::InputID, InputStatesList::InputName, InputStatesList::InputLabel,
                                          InputStatesList::InputPriority, InputStatesList::InputDate};
      return FiniteStateMachine(states, context);
    }
    if (stateMachine == FiniteStateMachinesList::Postpone) {
      std::vector<InputStatesList> states{InputStatesList::InputID, InputStatesList::InputDate};
      return FiniteStateMachine(states, context);
    }
  }

static std::shared_ptr<State> CreateState(const StatesList &state) {
    if (state == StatesList::AddTask) {
      return std::make_shared<AddTaskState>();
    }
    if (state == StatesList::AddSubtask) {
      return std::make_shared<AddSubtaskState>();
    }
    if (state == StatesList::Postpone) {
      return std::make_shared<PostponeState>();
    }
    if (state == StatesList::Delete) {
      return std::make_shared<DeleteState>();
    }
    if (state == StatesList::Complete) {
      return std::make_shared<CompleteState>();
    }
    if (state == StatesList::ShowToday) {
      return std::make_shared<ShowTodayState>();
    }
    if (state == StatesList::ShowThisWeek) {
      return std::make_shared<ShowThisWeekState>();
    }
    if (state == StatesList::ShowByName) {
      return std::make_shared<ShowByNameState>();
    }
    if (state == StatesList::ShowByLabel) {
      return std::make_shared<ShowByLabelState>();
    }
    if (state == StatesList::ShowByID) {
      return std::make_shared<ShowByIDState>();
    }
    if (state == StatesList::ShowAll) {
      return std::make_shared<ShowAllState>();
    }
    if (state == StatesList::Base) {
      return std::make_shared<BaseState>();
    }
}
static std::shared_ptr<InputState> CreateInputState(const InputStatesList &state) {
    if (state == InputStatesList::InputName) {
      return std::make_shared<InputNameState>();
    }
    if (state == InputStatesList::InputLabel) {
      return std::make_shared<InputLabelState>();
    }
    if (state == InputStatesList::InputPriority) {
      return std::make_shared<InputPriorityState>();
    }
    if (state == InputStatesList::InputDate) {
      return std::make_shared<InputDateState>();
    }
    if (state == InputStatesList::InputID) {
      return std::make_shared<InputIDState>();
    }
  }
}

#endif //TASKMANAGER_CLI_FACTORY_H_
