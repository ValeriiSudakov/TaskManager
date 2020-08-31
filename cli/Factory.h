//
// Created by valeriisudakov on 27.08.20.
//

#ifndef TASKMANAGER_CLI_FACTORY_H_
#define TASKMANAGER_CLI_FACTORY_H_
#include "StatesControllers/FiniteStateMachine.h"
#include "StatesControllers/FiniteStateMachinesList.h"
#include "States/StatesID.h"
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
      std::map<StatesID, std::map<StateOperationResult, StatesID>> stateTransitionTable;

      stateTransitionTable[StatesID::InputName][StateOperationResult::SUCCESS]         = StatesID::InputLabel;
      stateTransitionTable[StatesID::InputName][StateOperationResult::INCORRECT_INPUT] = StatesID::InputName;

      stateTransitionTable[StatesID::InputLabel][StateOperationResult::SUCCESS]         = StatesID::InputPriority;
      stateTransitionTable[StatesID::InputLabel][StateOperationResult::INCORRECT_INPUT] = StatesID::InputLabel;

      stateTransitionTable[StatesID::InputPriority][StateOperationResult::SUCCESS]         = StatesID::InputDate;
      stateTransitionTable[StatesID::InputPriority][StateOperationResult::INCORRECT_INPUT] = StatesID::InputPriority;

      stateTransitionTable[StatesID::InputDate][StateOperationResult::SUCCESS]         = StatesID::Exit;
      stateTransitionTable[StatesID::InputDate][StateOperationResult::INCORRECT_INPUT] = StatesID::InputDate;

        return FiniteStateMachine(stateTransitionTable, StatesID::InputName, context);
      }

    if (stateMachine == FiniteStateMachinesList::AddSubtask) {
      std::map<StatesID, std::map<StateOperationResult, StatesID>> stateTransitionTable;

      stateTransitionTable[StatesID::ShowAll][StateOperationResult::SUCCESS]          = StatesID::InputID;
      stateTransitionTable[StatesID::ShowAll][StateOperationResult::INCORRECT_INPUT]  = StatesID::ShowAll;
      stateTransitionTable[StatesID::ShowAll][StateOperationResult::TASKS_LIST_EMPTY] = StatesID::Exit;

      stateTransitionTable[StatesID::InputID][StateOperationResult::SUCCESS]         = StatesID::InputName;
      stateTransitionTable[StatesID::InputID][StateOperationResult::INCORRECT_INPUT] = StatesID::InputID;

      stateTransitionTable[StatesID::InputName][StateOperationResult::SUCCESS]         = StatesID::InputLabel;
      stateTransitionTable[StatesID::InputName][StateOperationResult::INCORRECT_INPUT] = StatesID::InputName;

      stateTransitionTable[StatesID::InputLabel][StateOperationResult::SUCCESS]         = StatesID::InputPriority;
      stateTransitionTable[StatesID::InputLabel][StateOperationResult::INCORRECT_INPUT] = StatesID::InputLabel;

      stateTransitionTable[StatesID::InputPriority][StateOperationResult::SUCCESS]         = StatesID::InputDate;
      stateTransitionTable[StatesID::InputPriority][StateOperationResult::INCORRECT_INPUT] = StatesID::InputPriority;

      stateTransitionTable[StatesID::InputDate][StateOperationResult::SUCCESS]         = StatesID::Exit;
      stateTransitionTable[StatesID::InputDate][StateOperationResult::INCORRECT_INPUT] = StatesID::InputDate;

      return FiniteStateMachine(stateTransitionTable, StatesID::ShowAll, context);
    }
    if (stateMachine == FiniteStateMachinesList::Postpone) {
      std::map<StatesID, std::map<StateOperationResult, StatesID>> stateTransitionTable;

      stateTransitionTable[StatesID::ShowAll][StateOperationResult::SUCCESS]         = StatesID::InputID;
      stateTransitionTable[StatesID::ShowAll][StateOperationResult::INCORRECT_INPUT] = StatesID::ShowAll;
      stateTransitionTable[StatesID::ShowAll][StateOperationResult::TASKS_LIST_EMPTY] = StatesID::Exit;

      stateTransitionTable[StatesID::InputID][StateOperationResult::SUCCESS]         = StatesID::InputDate;
      stateTransitionTable[StatesID::InputID][StateOperationResult::INCORRECT_INPUT] = StatesID::InputID;

      stateTransitionTable[StatesID::InputDate][StateOperationResult::SUCCESS]         = StatesID::Exit;
      stateTransitionTable[StatesID::InputDate][StateOperationResult::INCORRECT_INPUT] = StatesID::InputDate;

      return FiniteStateMachine(stateTransitionTable, StatesID::ShowAll, context);
    }


    if (stateMachine == FiniteStateMachinesList::InputID) {
      std::map<StatesID, std::map<StateOperationResult, StatesID>> stateTransitionTable;

      stateTransitionTable[StatesID::ShowAll][StateOperationResult::SUCCESS]         = StatesID::InputID;
      stateTransitionTable[StatesID::ShowAll][StateOperationResult::INCORRECT_INPUT] = StatesID::ShowAll;
      stateTransitionTable[StatesID::ShowAll][StateOperationResult::TASKS_LIST_EMPTY] = StatesID::Exit;

      stateTransitionTable[StatesID::InputID][StateOperationResult::SUCCESS]         = StatesID::Exit;
      stateTransitionTable[StatesID::InputID][StateOperationResult::INCORRECT_INPUT] = StatesID::InputID;

      return FiniteStateMachine(stateTransitionTable, StatesID::ShowAll, context);
    }
    if (stateMachine == FiniteStateMachinesList::ShowByName) {
      std::map<StatesID, std::map<StateOperationResult, StatesID>> stateTransitionTable;

      stateTransitionTable[StatesID::InputName][StateOperationResult::SUCCESS]         = StatesID::Exit;
      stateTransitionTable[StatesID::InputName][StateOperationResult::INCORRECT_INPUT] = StatesID::InputName;

      return FiniteStateMachine(stateTransitionTable, StatesID::InputName, context);
    }
    if (stateMachine == FiniteStateMachinesList::ShowByLabel) {
      std::map<StatesID, std::map<StateOperationResult, StatesID>> stateTransitionTable;

      stateTransitionTable[StatesID::InputLabel][StateOperationResult::SUCCESS]         = StatesID::Exit;
      stateTransitionTable[StatesID::InputLabel][StateOperationResult::INCORRECT_INPUT] = StatesID::InputLabel;

      return FiniteStateMachine(stateTransitionTable, StatesID::InputLabel, context);
    }
  }

  static std::shared_ptr<State> CreateState(const StatesID &state) {
    if (state == StatesID::AddTask) {
      return std::make_shared<AddTaskState>();
    }
    if (state == StatesID::AddSubtask) {
      return std::make_shared<AddSubtaskState>();
    }
    if (state == StatesID::Postpone) {
      return std::make_shared<PostponeState>();
    }
    if (state == StatesID::Delete) {
      return std::make_shared<DeleteState>();
    }
    if (state == StatesID::Complete) {
      return std::make_shared<CompleteState>();
    }
    if (state == StatesID::ShowToday) {
      return std::make_shared<ShowTodayState>();
    }
    if (state == StatesID::ShowThisWeek) {
      return std::make_shared<ShowThisWeekState>();
    }
    if (state == StatesID::ShowByName) {
      return std::make_shared<ShowByNameState>();
    }
    if (state == StatesID::ShowByLabel) {
      return std::make_shared<ShowByLabelState>();
    }
    if (state == StatesID::ShowByID) {
      return std::make_shared<ShowByIDState>();
    }
    if (state == StatesID::ShowAll) {
      return std::make_shared<ShowAllState>();
    }
    if (state == StatesID::Base) {
      return std::make_shared<BaseState>();
    }
    if (state == StatesID::InputName) {
      return std::make_shared<InputNameState>();
    }
    if (state == StatesID::InputLabel) {
      return std::make_shared<InputLabelState>();
    }
    if (state == StatesID::InputPriority) {
      return std::make_shared<InputPriorityState>();
    }
    if (state == StatesID::InputDate) {
      return std::make_shared<InputDateState>();
    }
    if (state == StatesID::InputID) {
      return std::make_shared<InputIDState>();
    }
    if (state == StatesID::Exit) {
      return nullptr;
    }
  }
}

#endif //TASKMANAGER_CLI_FACTORY_H_
