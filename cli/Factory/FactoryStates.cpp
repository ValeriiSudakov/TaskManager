//
// Created by valeriisudakov on 11.09.20.
//
#include "FactoryStates.h"
#include "States/StatesID.h"
#include "States/EditSystemStates/AddTaskState.h"
#include "States/EditSystemStates/AddSubtaskState.h"
#include "States/EditSystemStates/CompleteState.h"
#include "States/EditSystemStates/DeleteState.h"
#include "States/EditSystemStates/PostponeState.h"
#include "States/EditSystemStates/LoadState.h"
#include "States/EditSystemStates/SaveState.h"

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

#include "LazyInitClass.h"

FactoryStates::FactoryStates() {
  menuStates_[StatesID::BASE_MENU] = nullptr;
  menuStates_[StatesID::CONTINUE_MENU] = nullptr;

  states_[StatesID::ADD_TASK] = std::make_unique<LazyInitClass<AddTaskState>>();
  states_[StatesID::ADD_SUBTASK] = std::make_unique<LazyInitClass<AddSubtaskState>>();
  states_[StatesID::POSTPONE] = std::make_unique<LazyInitClass<PostponeState  >>();
  states_[StatesID::COMPLETE] = std::make_unique<LazyInitClass<CompleteState>>();
  states_[StatesID::DELETE] = std::make_unique<LazyInitClass<DeleteState>>();
  states_[StatesID::LOAD] = std::make_unique<LazyInitClass<LoadState>>();
  states_[StatesID::SAVE] = std::make_unique<LazyInitClass<SaveState>>();

  states_[StatesID::INPUT_TASK] = std::make_unique<LazyInitClass<InputTask>>();
  states_[StatesID::INPUT_DATE] = std::make_unique<LazyInitClass<InputDateState>>();
  states_[StatesID::INPUT_PRIORITY] = std::make_unique<LazyInitClass<InputPriorityState>>();
  states_[StatesID::INPUT_LABEL] = std::make_unique<LazyInitClass<InputLabelState>>();
  states_[StatesID::INPUT_NAME] = std::make_unique<LazyInitClass<InputNameState>>();
  states_[StatesID::INPUT_ID] = std::make_unique<LazyInitClass<InputIDState>>();

  states_[StatesID::SHOW_ALL] = std::make_unique<LazyInitClass<ShowAllState>>();
  states_[StatesID::SHOW_BY_ID] = std::make_unique<LazyInitClass<ShowByIDState>>();
  states_[StatesID::SHOW_BY_LABEL] = std::make_unique<LazyInitClass<ShowByLabelState>>();
  states_[StatesID::SHOW_BY_NAME] = std::make_unique<LazyInitClass<ShowByNameState>>();
  states_[StatesID::SHOW_TODAY] = std::make_unique<LazyInitClass<ShowTodayState>>();
  states_[StatesID::SHOW_THIS_WEEK] = std::make_unique<LazyInitClass<ShowThisWeekState>>();

}


std::shared_ptr<State> FactoryStates::Create(StatesID id){
  if (StatesID::EXIT == id){
    return nullptr;
  }
  auto menu = menuStates_.find(id);
  if (menuStates_.end() != menu){
    if (nullptr == menu->second){
      menu->second = CreateMenu(menu->first);
    }
    return menu->second;
  }

  auto state = states_.find(id);
  if (states_.end() != state){
    if (id == state->first){
      return state->second->Create();
    }
  }

  // if State does not exist
  return nullptr;
}

std::shared_ptr<State>  CreateMenu(StatesID id){
  if (StatesID::BASE_MENU == id){
    std::unique_ptr<Actions> actions = std::make_unique<Actions>();
    actions->edit_.insert(std::make_pair("add task",      StatesID::ADD_TASK));
    actions->edit_.insert(std::make_pair("save",          StatesID::SAVE));
    actions->edit_.insert(std::make_pair("load",          StatesID::LOAD));
    actions->show_.insert(std::make_pair("show all",      StatesID::SHOW_ALL));
    actions->show_.insert(std::make_pair("show this week",StatesID::SHOW_THIS_WEEK));
    actions->show_.insert(std::make_pair("show today",    StatesID::SHOW_TODAY));
    actions->show_.insert(std::make_pair("show by name",  StatesID::SHOW_BY_NAME));
    actions->show_.insert(std::make_pair("show by label", StatesID::SHOW_BY_LABEL));
    actions->exit_.first = "exit";
    actions->exit_.second = StatesID::EXIT;

    return std::move(std::make_shared<Menu>(StatesID::BASE_MENU, std::move(actions)));
  }
  else if (StatesID::CONTINUE_MENU == id){
    std::unique_ptr<Actions> actions = std::make_unique<Actions>();
    actions->edit_.insert(std::make_pair("add subtask", StatesID::ADD_SUBTASK));
    actions->edit_.insert(std::make_pair("remove", StatesID::DELETE));
    actions->edit_.insert(std::make_pair("complete", StatesID::COMPLETE));
    actions->edit_.insert(std::make_pair("postpone", StatesID::POSTPONE));
    actions->show_.insert(std::make_pair("show by id", StatesID::SHOW_BY_ID));
    actions->exit_.first = "back";
    actions->exit_.second = StatesID::BASE_MENU;

    return std::move(std::make_shared<Menu>(StatesID::CONTINUE_MENU, std::move(actions)));
  }
}
