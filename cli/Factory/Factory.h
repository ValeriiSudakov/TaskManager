//
// Created by valeriisudakov on 27.08.20.
//

#ifndef TASKMANAGER_CLI_FACTORY_H_
#define TASKMANAGER_CLI_FACTORY_H_

#include "StatesControllers/StateMachine.h"
#include "StatesControllers/FiniteStateMachine.h"
#include "IO_Layer.h"

#include "States/StatesID.h"
#include "States/EditSystemStates/AddTaskState.h"
#include "States/EditSystemStates/AddSubtaskState.h"
#include "States/EditSystemStates/CompleteState.h"
#include "States/EditSystemStates/DeleteState.h"
#include "States/EditSystemStates/PostponeState.h"

#include "States/InputStates/InputTask.h"
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
#include "States/Menus/Menu.h"


namespace Factory {


   static std::shared_ptr<State> CreateState(const StatesID &state) {
    if (state == StatesID::AddTask) {
      return std::make_shared<AddTaskState>();
    }
    if (state == StatesID::InputTask) {
      return std::make_shared<InputTask>();
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
    if (state == StatesID::BaseMenu) {
      std::unique_ptr<Actions> actions = std::make_unique<Actions>();
      actions->edit_.insert(std::make_pair("add task",      StatesID::AddTask));
      actions->show_.insert(std::make_pair("show all",      StatesID::ShowAll));
      actions->show_.insert(std::make_pair("show this week",StatesID::ShowThisWeek));
      actions->show_.insert(std::make_pair("show today",    StatesID::ShowToday));
      actions->show_.insert(std::make_pair("show by name",  StatesID::ShowByName));
      actions->show_.insert(std::make_pair("show by label", StatesID::ShowByLabel));
      actions->exit_.first = "exit";
      actions->exit_.second = StatesID::Exit;

      return std::make_shared<Menu>(StatesID::BaseMenu, std::move(actions));
    }
    if (state == StatesID::ContinueMenu) {
      std::unique_ptr<Actions> actions = std::make_unique<Actions>();
      actions->edit_.insert(std::make_pair("add subtask", StatesID::AddSubtask));
      actions->edit_.insert(std::make_pair("remove", StatesID::Delete));
      actions->edit_.insert(std::make_pair("complete", StatesID::Complete));
      actions->edit_.insert(std::make_pair("postpone", StatesID::Postpone));
      actions->show_.insert(std::make_pair("show by id", StatesID::ShowByID));
      actions->exit_.first = "back to menu";
      actions->exit_.second = StatesID::BaseMenu;

      return std::make_shared<Menu>(StatesID::ContinueMenu, std::move(actions));
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
