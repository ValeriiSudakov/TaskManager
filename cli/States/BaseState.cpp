//
// Created by valeriisudakov on 18.08.20.
//

#include "BaseState.h"
#include "States/InputStates/InputDateState.h"
#include "States/InputStates/InputLabelState.h"
#include "States/InputStates/InputNameState.h"
#include "States/InputStates/InputPriorityState.h"
#include "States/InputStates/InputIDState.h"
#include "States/EditSystemStates/AddSubtaskState.h"
#include "States/EditSystemStates/AddTaskState.h"
#include "States/EditSystemStates/CompleteState.h"
#include "States/EditSystemStates/DeleteState.h"
#include "States/EditSystemStates/PostponeState.h"
#include "States/ShowStates/ShowAllState.h"
#include "States/ShowStates/ShowByNameState.h"
#include "States/ShowStates/ShowByLabelState.h"
#include "States/ShowStates/ShowByIDState.h"
#include "States/ShowStates/ShowTodayState.h"
#include "States/ShowStates/ShowThisWeekState.h"


BaseState::BaseState() {
  stateName_ = "base";
}

BaseState::~BaseState() = default;

void BaseState::Do(Context& context){
  //is waiting
}

void BaseState::PrintNextStates() {
  std::cout<<"add task"<<std::endl;
  std::cout<<"add subtask"<<std::endl;
  std::cout<<"show by ID"<<std::endl;
  std::cout<<"show all"<<std::endl;
  std::cout<<"show today"<<std::endl;
  std::cout<<"show this week"<<std::endl;
  std::cout<<"show by name"<<std::endl;
  std::cout<<"show by label"<<std::endl;
  std::cout<<"postpone"<<std::endl;
  std::cout<<"remove"<<std::endl;
  std::cout<<"complete"<<std::endl;
  std::cout<<"exit"<<std::endl;
}

std::shared_ptr<State> BaseState::ReadAction() {
  PrintNextStates();
  std::cout<<"input next state: ";
  std::string input;

  std::getline(std::cin, input);
  if (input == "add task"){
    auto addTaskState  = std::make_shared<AddTaskState>();
    auto inputDate     = std::make_shared<InputDateState>(std::move(addTaskState));
    auto inputPriority = std::make_shared<InputPriorityState>(std::move(inputDate));
    auto inputLabel    = std::make_shared<InputLabelState>(std::move(inputPriority));
    auto inputName     = std::make_shared<InputNameState>(std::move(inputLabel));
    return std::move(inputName);

  } else if (input == "add subtask") {
    auto addSubtaskState = std::make_shared<AddSubtaskState>();
    auto inputDate       = std::make_shared<InputDateState>(std::move(addSubtaskState));
    auto inputPriority   = std::make_shared<InputPriorityState>(std::move(inputDate));
    auto inputLabel      = std::make_shared<InputLabelState>(std::move(inputPriority));
    auto inputName       = std::make_shared<InputNameState>(std::move(inputLabel));
    auto inputID         = std::make_shared<InputIDState>(std::move(inputName));
    return std::move(inputID);

  } else if (input == "show all"){
    return std::move(std::make_shared<ShowAllState>());

  } else if (input == "show this week"){
    return std::move(std::make_shared<ShowThisWeekState>());

  } else if (input == "show by ID"){
    auto showByID = std::make_shared<ShowByIDState>();
    auto inputID  = std::make_shared<InputIDState>(std::move(showByID));
    return inputID;

  } else if (input == "show by name"){
    auto showByName = std::make_shared<ShowByNameState>();
    auto inputName  = std::make_shared<InputNameState>(std::move(showByName));
    return std::move(inputName);

  } else if (input == "show today"){
    return std::move(std::make_shared<ShowTodayState>());

  } else if (input == "show by label"){
    auto showByLabel = std::make_shared<ShowByLabelState>();
    auto inputName   = std::make_shared<InputLabelState>(std::move(showByLabel));
    return std::move(inputName);

  } else if (input == "postpone"){
    auto postpone  = std::make_shared<PostponeState>();
    auto inputDate = std::make_shared<InputDateState>(std::move(postpone));
    auto inputID   = std::make_shared<InputIDState>(std::move(inputDate));
    return std::move(inputID);

  } else if (input == "remove"){
    auto Delete   = std::make_shared<DeleteState>();
    auto inputID  = std::make_shared<InputIDState>(std::move(Delete));
    return std::move(inputID);

  } else if (input == "complete") {
    auto complete = std::make_shared<CompleteState>();
    auto inputID  = std::make_shared<InputIDState>(std::move(complete));
    return std::move(inputID);

  } else if (input == "exit"){
    return nullptr;

  }
  else {
    return std::move(std::make_shared<BaseState>());
  }
}
