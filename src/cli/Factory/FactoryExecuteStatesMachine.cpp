//
// Created by valeriisudakov on 13.09.20.
//
#include "StatesControllers/ExecuteStatesMachine.h"
#include "StatesControllers/StateMachineMenu.h"
#include "FactoryExecuteStatesMachine.h"

FactoryExecuteStatesMachine::FactoryExecuteStatesMachine(){
  stateMachines_[FiniteStateMachineID::INPUT_ID] = nullptr;
  stateMachines_[FiniteStateMachineID::INPUT_DATE] = nullptr;
  stateMachines_[FiniteStateMachineID::INPUT_LABEL] = nullptr;
  stateMachines_[FiniteStateMachineID::INPUT_NAME] = nullptr;
  stateMachines_[FiniteStateMachineID::INPUT_FILE_NAME] = nullptr;
  stateMachines_[FiniteStateMachineID::POSTPONE] = nullptr;
  stateMachines_[FiniteStateMachineID::INPUT_SUBTASK_PARAMS] = nullptr;
  stateMachines_[FiniteStateMachineID::INPUT_TASK_PARAMS] = nullptr;

}

FactoryExecuteStatesMachine::~FactoryExecuteStatesMachine() = default;

std::shared_ptr<StateMachine> FactoryExecuteStatesMachine::CreateMenu(const StatesID &id,
                                                                      const std::shared_ptr<Context> &context,
                                                                      InputOutputLayer &io) {
  return std::make_shared<StateMachineMenu>(id, context, io);

}

std::shared_ptr<StateMachine> FactoryExecuteStatesMachine::CreateAfterMenuStatesMachine(const StatesID &stateID,
                                                                                        const std::shared_ptr<Context> &context,
                                                                                        InputOutputLayer &io) {
  return std::make_shared<ExecuteStatesMachine>(
      std::vector<StatesID>{
          stateID,
          StatesID::EXIT
      },
      context,
      io);
}


std::shared_ptr<StateMachine> FactoryExecuteStatesMachine::Create(const FiniteStateMachineID &id,
                                                                  const std::shared_ptr<Context> &context,
                                                                  InputOutputLayer &io) {
  auto stateMachine = stateMachines_.find(id);
  if (stateMachines_.end() == stateMachine){
    return nullptr;
  }

  if (FiniteStateMachineID::INPUT_ID == stateMachine->first){
    stateMachine->second = std::make_shared<ExecuteStatesMachine>(
                                              std::vector<StatesID>{
                                                  StatesID::INPUT_ID,
                                                  StatesID::EXIT
                                              },
                                              context,
                                              io);

  }
  else if (FiniteStateMachineID::INPUT_DATE == stateMachine->first){
    stateMachine->second = std::make_shared<ExecuteStatesMachine>(
                                              std::vector<StatesID>{
                                                  StatesID::INPUT_DATE,
                                                  StatesID::EXIT
                                              },
                                              context,
                                              io);

  }
  else if (FiniteStateMachineID::INPUT_LABEL == stateMachine->first){
    stateMachine->second = std::make_shared<ExecuteStatesMachine>(
                                                std::vector<StatesID>{
                                                    StatesID::INPUT_LABEL,
                                                    StatesID::EXIT
                                                },
                                                context,
                                                io);

  }
  else if (FiniteStateMachineID::INPUT_NAME == stateMachine->first){

    stateMachine->second = std::make_shared<ExecuteStatesMachine>(
                                              std::vector<StatesID>{
                                                  StatesID::INPUT_NAME,
                                                  StatesID::EXIT
                                              },
                                              context,
                                              io);

  }
  else if (FiniteStateMachineID::INPUT_FILE_NAME == stateMachine->first){

    stateMachine->second = std::make_shared<ExecuteStatesMachine>(
        std::vector<StatesID>{
            StatesID::INPUT_FILE_NAME,
            StatesID::EXIT
        },
        context,
        io);

  }
  else if (FiniteStateMachineID::POSTPONE == stateMachine->first){
    stateMachine->second = std::make_shared<ExecuteStatesMachine>(
        std::vector<StatesID>{
            StatesID::INPUT_ID,
            StatesID::INPUT_DATE,
            StatesID::EXIT
        },
        context,
        io);

  }
  else if (FiniteStateMachineID::INPUT_TASK_PARAMS == stateMachine->first){
    stateMachine->second = std::make_shared<ExecuteStatesMachine>(
                                              std::vector<StatesID>{
                                                  StatesID::INPUT_NAME,
                                                  StatesID::INPUT_LABEL,
                                                  StatesID::INPUT_PRIORITY,
                                                  StatesID::INPUT_DATE,
                                                  StatesID::EXIT
                                              },
                                              context,
                                              io);

  }
  else if (FiniteStateMachineID::INPUT_SUBTASK_PARAMS == stateMachine->first){
    stateMachine->second = std::make_shared<ExecuteStatesMachine>(
                                      std::vector<StatesID>{
                                                  StatesID::INPUT_ID,
                                                  StatesID::INPUT_TASK,
                                                  StatesID::EXIT
                                              },
                                              context,
                                              io);

  }

  return stateMachine->second;
}