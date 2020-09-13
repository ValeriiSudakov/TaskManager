//
// Created by valeriisudakov on 13.09.20.
//
#include "StatesControllers/FiniteStateMachine.h"
#include "StatesControllers/StateMachineMenu.h"
#include "FactoryFiniteStatesMachines.h"

FactoryFiniteStatesMachines::FactoryFiniteStatesMachines(){
  stateMachines_[FiniteStateMachineID::INPUT_ID] = nullptr;
  stateMachines_[FiniteStateMachineID::INPUT_DATE] = nullptr;
  stateMachines_[FiniteStateMachineID::INPUT_LABEL] = nullptr;
  stateMachines_[FiniteStateMachineID::INPUT_NAME] = nullptr;
  stateMachines_[FiniteStateMachineID::POSTPONE] = nullptr;
  stateMachines_[FiniteStateMachineID::INPUT_SUBTASK_PARAMS] = nullptr;
  stateMachines_[FiniteStateMachineID::INPUT_TASK_PARAMS] = nullptr;

}

FactoryFiniteStatesMachines::~FactoryFiniteStatesMachines() = default;

std::shared_ptr<StateMachine> FactoryFiniteStatesMachines::CreateMenu(const StatesID& id,
                                                                      const std::shared_ptr<Context>& context,
                                                                      std::unique_ptr<InputOutputLayer> io) {

  return std::move(std::make_shared<StateMachineMenu>(id, context, std::move(io)));

}

std::shared_ptr<StateMachine> FactoryFiniteStatesMachines::CreateAfterMenuState(const StatesID& stateID,
                                                                                const std::shared_ptr<Context> &context,
                                                                                std::unique_ptr<InputOutputLayer> io) {
  return std::move(std::make_shared<FiniteStateMachine>(
                                          std::list<StatesID>{
                                              stateID,
                                              StatesID::EXIT
                                          },
                                          context,
                                          std::move(io)));

}


std::shared_ptr<StateMachine> FactoryFiniteStatesMachines::Create(const FiniteStateMachineID& id,
                                                                  const std::shared_ptr<Context>& context,
                                                                        std::unique_ptr<InputOutputLayer> io) {



  auto stateMachine = stateMachines_.find(id);
  if (stateMachines_.end() == stateMachine){
    return nullptr;
  }

  if (FiniteStateMachineID::INPUT_ID == stateMachine->first){
    if (!stateMachine->second) {
      stateMachine->second = std::make_shared<FiniteStateMachine>(
                                                std::list<StatesID>{
                                                    StatesID::INPUT_ID,
                                                    StatesID::EXIT
                                                },
                                                context,
                                                std::move(io));
      }
  }
  else if (FiniteStateMachineID::INPUT_DATE == stateMachine->first){
    if (!stateMachine->second){
      stateMachine->second = std::make_shared<FiniteStateMachine>(
                                                std::list<StatesID>{
                                                    StatesID::INPUT_DATE,
                                                    StatesID::EXIT
                                                },
                                                context,
                                                std::move(io));
    }
  }
  else if (FiniteStateMachineID::INPUT_LABEL == stateMachine->first){
    if (!stateMachine->second){
      stateMachine->second = std::make_shared<FiniteStateMachine>(
                                                  std::list<StatesID>{
                                                      StatesID::INPUT_LABEL,
                                                      StatesID::EXIT
                                                  },
                                                  context,
                                                  std::move(io));
    }
  }
  else if (FiniteStateMachineID::INPUT_NAME == stateMachine->first){
    if (!stateMachine->second){
      stateMachine->second = std::make_shared<FiniteStateMachine>(
                                                std::list<StatesID>{
                                                    StatesID::INPUT_NAME,
                                                    StatesID::EXIT
                                                },
                                                context,
                                                std::move(io));
    }
  }
  else if (FiniteStateMachineID::POSTPONE == stateMachine->first){
    if (!stateMachine->second){
      stateMachine->second = std::make_shared<FiniteStateMachine>(
          std::list<StatesID>{
              StatesID::INPUT_ID,
              StatesID::INPUT_DATE,
              StatesID::EXIT
          },
          context,
          std::move(io));
    }
  }
  else if (FiniteStateMachineID::INPUT_TASK_PARAMS == stateMachine->first){
    if (!stateMachine->second){
      stateMachine->second = std::make_shared<FiniteStateMachine>(
                                                std::list<StatesID>{
                                                    StatesID::INPUT_NAME,
                                                    StatesID::INPUT_LABEL,
                                                    StatesID::INPUT_PRIORITY,
                                                    StatesID::INPUT_DATE,
                                                    StatesID::EXIT
                                                },
                                                context,
                                                std::move(io));
    }
  }
  else if (FiniteStateMachineID::INPUT_SUBTASK_PARAMS == stateMachine->first){
    if (!stateMachine->second){
      stateMachine->second = std::make_shared<FiniteStateMachine>(
                                                std::list<StatesID>{
                                                    StatesID::INPUT_ID,
                                                    StatesID::INPUT_TASK,
                                                    StatesID::EXIT
                                                },
                                                context,
                                                std::move(io));
    }
  }
  return stateMachine->second;

}