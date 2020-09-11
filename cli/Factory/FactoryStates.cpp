//
// Created by valeriisudakov on 11.09.20.
//

#include "States/Menus/MenuActions.h"
#include "FactoryStates.h"
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

#include "States/Menus/MenuActions.h"

#include "LasyInitClass.h"

FactoryStates::FactoryStates() {
  menuStates_[StatesID::BaseMenu] = nullptr;
  menuStates_[StatesID::ContinueMenu] = nullptr;

  states_[StatesID::AddTask] = std::make_unique<LasyInitClass<AddTaskState>>();
  states_[StatesID::AddSubtask] = std::make_unique<LasyInitClass<AddSubtaskState>>();
  states_[StatesID::Postpone] = std::make_unique<LasyInitClass<PostponeState  >>();
  states_[StatesID::Complete] = std::make_unique<LasyInitClass<CompleteState>>();
  states_[StatesID::Delete] = std::make_unique<LasyInitClass<DeleteState>>();

  states_[StatesID::InputTask] = std::make_unique<LasyInitClass<InputTask>>();
  states_[StatesID::InputDate] = std::make_unique<LasyInitClass<InputDateState>>();
  states_[StatesID::InputPriority] = std::make_unique<LasyInitClass<InputPriorityState>>();
  states_[StatesID::InputLabel] = std::make_unique<LasyInitClass<InputLabelState>>();
  states_[StatesID::InputName] = std::make_unique<LasyInitClass<InputNameState>>();
  states_[StatesID::InputID] = std::make_unique<LasyInitClass<InputIDState>>();

  states_[StatesID::ShowAll] = std::make_unique<LasyInitClass<ShowAllState>>();
  states_[StatesID::ShowByID] = std::make_unique<LasyInitClass<ShowByIDState>>();
  states_[StatesID::ShowByLabel] = std::make_unique<LasyInitClass<ShowByLabelState>>();
  states_[StatesID::ShowByName] = std::make_unique<LasyInitClass<ShowByNameState>>();
  states_[StatesID::ShowToday] = std::make_unique<LasyInitClass<ShowTodayState>>();
  states_[StatesID::ShowThisWeek] = std::make_unique<LasyInitClass<ShowThisWeekState>>();

}


std::shared_ptr<State> FactoryStates::Create(StatesID id){
  if (StatesID::Exit == id){
    return nullptr;
  }
  for (auto& menu : menuStates_){
    if (id == menu.first){
      if (nullptr == menu.second){
        menu.second = CreateMenu(menu.first);
      }
      return menu.second;
    }
  }
  for (auto& state : states_){
    if (id == state.first){
      return state.second->Create();
    }
  }
}

std::shared_ptr<State>  CreateMenu(StatesID id){
  if (StatesID::BaseMenu == id){
    std::unique_ptr<Actions> actions = std::make_unique<Actions>();
    actions->edit_.insert(std::make_pair("add task",      StatesID::AddTask));
    actions->show_.insert(std::make_pair("show all",      StatesID::ShowAll));
    actions->show_.insert(std::make_pair("show this week",StatesID::ShowThisWeek));
    actions->show_.insert(std::make_pair("show today",    StatesID::ShowToday));
    actions->show_.insert(std::make_pair("show by name",  StatesID::ShowByName));
    actions->show_.insert(std::make_pair("show by label", StatesID::ShowByLabel));
    actions->exit_.first = "exit";
    actions->exit_.second = StatesID::Exit;

    return std::move(std::make_shared<Menu>(StatesID::BaseMenu, std::move(actions)));
  }
  else if (StatesID::ContinueMenu == id){
    std::unique_ptr<Actions> actions = std::make_unique<Actions>();
    actions->edit_.insert(std::make_pair("add subtask", StatesID::AddSubtask));
    actions->edit_.insert(std::make_pair("remove", StatesID::Delete));
    actions->edit_.insert(std::make_pair("complete", StatesID::Complete));
    actions->edit_.insert(std::make_pair("postpone", StatesID::Postpone));
    actions->show_.insert(std::make_pair("show by id", StatesID::ShowByID));
    actions->exit_.first = "back to menu";
    actions->exit_.second = StatesID::BaseMenu;

    return std::move(std::make_shared<Menu>(StatesID::ContinueMenu, std::move(actions)));
  }
}
