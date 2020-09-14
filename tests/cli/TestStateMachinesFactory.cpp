//
// Created by valeriisudakov on 14.09.20.
//

#include <gtest/gtest.h>
#include "Factory/FactoryExecuteStatesMachine.h"
#include "InputOutputConsoleLayer.h"
#include <memory>

class TestStatesMachineFactory :  public ::testing::Test {
 protected:
  virtual void SetUp() override{
    context = std::make_shared<Context>(nullptr);
    io = std::make_shared<InputOutputConsoleLayer>();
  }

  std::shared_ptr<Context> context;
  std::shared_ptr<InputOutputLayer> io;
};

TEST_F(TestStatesMachineFactory, shouldCorrectCreateAfterMenu) {
  FactoryExecuteStatesMachine factory;

  auto show = factory.CreateAfterMenuStatesMachine(StatesID::SHOW, context, *io);
  ASSERT_NE(show, nullptr);

  auto edit = factory.CreateAfterMenuStatesMachine(StatesID::EDIT, context, *io);
  ASSERT_NE(edit, nullptr);

}

TEST_F(TestStatesMachineFactory, shouldCorrectCreateMenu){
  FactoryExecuteStatesMachine factory;

  auto baseMenu = factory.CreateMenu(StatesID::BASE_MENU, context, *io);
  ASSERT_NE(baseMenu, nullptr);

  auto continueMenu = factory.CreateMenu(StatesID::CONTINUE_MENU, context, *io);
  ASSERT_NE(continueMenu, nullptr);

}

TEST_F(TestStatesMachineFactory, shouldCorrectCreate){
  FactoryExecuteStatesMachine factory;

  auto inputName = factory.Create(FiniteStateMachineID::INPUT_NAME, context, *io);
  ASSERT_NE(inputName, nullptr);

  auto inputLabel = factory.Create(FiniteStateMachineID::INPUT_LABEL, context, *io);
  ASSERT_NE(inputName, nullptr);

  auto inputID = factory.Create(FiniteStateMachineID::INPUT_ID, context, *io);
  ASSERT_NE(inputID, nullptr);

  auto inputDate = factory.Create(FiniteStateMachineID::INPUT_DATE, context, *io);
  ASSERT_NE(inputDate, nullptr);

  auto postpone = factory.Create(FiniteStateMachineID::POSTPONE, context, *io);
  ASSERT_NE(postpone, nullptr);

  auto taskParams = factory.Create(FiniteStateMachineID::INPUT_TASK_PARAMS, context, *io);
  ASSERT_NE(taskParams, nullptr);

  auto subtaskParams = factory.Create(FiniteStateMachineID::INPUT_SUBTASK_PARAMS, context, *io);
  ASSERT_NE(subtaskParams, nullptr);
}