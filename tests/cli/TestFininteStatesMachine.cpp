//
// Created by valeriisudakov on 14.09.20.
//

#include <gtest/gtest.h>
#include "Factory.h"
#include <memory>
#include "mock/Service.h"
#include "mock/InputOutput.h"

using ::testing::Return;
using ::MockService;
using ::MockIO;

class TestFiniteStatesMachine :  public ::testing::Test {
 protected:
  void SetUp() override{

    io = std::make_shared<MockIO>();
    service = std::make_unique<MockService>();
    context = std::make_shared<Context>(*service);
  }

 protected:
  std::shared_ptr<MockIO> io;
  std::shared_ptr<Context> context;
  std::unique_ptr<MockService> service;
};

TEST_F(TestFiniteStatesMachine, shouldCorrectChangeStatesFiniteStatesMachine){
  // 5 times - "input smth" , 1 time  - "error"
  EXPECT_CALL(*io, Output).Times(6).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(5).WillOnce(Return("name"))
      .WillOnce(Return(""))
      .WillOnce(Return("Label"))
      .WillOnce(Return("first"))
      .WillOnce(Return("now"));

  auto stateMachine = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_TASK_PARAMS,
                                                         context,
                                                         *io);
  stateMachine->Execute();
}


TEST_F(TestFiniteStatesMachine, shouldCorrectChangeStatesMenuStatesMachine) {
  // + 10 - menus output
  // + 1 - input command
  // + 1 - command not found
  // + 1 - Empty line
  // + 10 - menu
  // + 1 - input command
  // + 4 - input data: "name, label, priority, date"
  // + 1 - success
  // + 1 - empty line
  // + 10 - menu
  // + 1 - input command
  // + 1 - empty line
 EXPECT_CALL(*io, Output).Times(42).WillRepeatedly(Return());
 EXPECT_CALL(*io, Input).Times(7).WillOnce(Return("adkjaskldjAKLSJLK!JKLJSA"))
                                      .WillOnce(Return("add task"))
                                      .WillOnce(Return("name"))
                                      .WillOnce(Return("label"))
                                      .WillOnce(Return("first"))
                                      .WillOnce(Return("now"))
                                      .WillOnce((Return("exit")));

  EXPECT_CALL(*service, AddTask).Times(1).WillOnce(Return(AddTaskResult::Success(TaskID())));
  auto inputNameMachine = Factory::CreateMenuStateMachine(StatesID::BASE_MENU,
                                                        context,
                                                        *io);

  inputNameMachine->Execute();
  ASSERT_EQ(context->buffer_.name, "name");
  ASSERT_EQ(context->buffer_.label, "label");
  ASSERT_EQ(context->buffer_.priority, Priority::FIRST);
  ASSERT_EQ(context->buffer_.date.Get().day_number(), Date::GetCurrentTime().day_number());
}
