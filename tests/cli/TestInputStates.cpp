//
// Created by valeriisudakov on 14.09.20.
//


#include "Factory/Factory.h"
#include <gtest/gtest.h>
#include <memory>
#include "mock/Service.h"
#include "mock/InputOutput.h"

using ::testing::Return;
using ::MockService;
using ::MockIO;

class TestInput :  public ::testing::Test {
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


TEST_F(TestInput, shouldCorrectInputName){
  EXPECT_CALL(*io, Output).Times(3).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(2).WillOnce(Return(""))
                                      .WillOnce(Return("name"));

  auto context = std::make_shared<Context>(*std::make_unique<MockService>());
  auto name = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_NAME,
                                                 context,
                                                 *io);
  name->Execute();
  ASSERT_EQ(context->buffer_.name, "name");
}

TEST_F(TestInput, shouldBeCorrectLabelInput){
  EXPECT_CALL(*io, Output).Times(3).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(2).WillOnce(Return(""))
      .WillOnce(Return("label"));

  auto label = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_LABEL,
                                                 context,
                                                  *io);
  label->Execute();
  ASSERT_EQ(context->buffer_.label, "label");
}


TEST_F(TestInput, shouldCorrectInputDate){
  EXPECT_CALL(*io, Output).Times(1).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("now"));
  auto date = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_DATE,
                                                  context,
                                                  *io);
  date->Execute();
  ASSERT_EQ(context->buffer_.date.Get().day_number(), Date::GetCurrentTime().day_number());
}

TEST_F(TestInput, shouldIncorrectInputDate){
  EXPECT_CALL(*io, Output).Times(3).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(2).WillOnce(Return("h1yuoas;jfnb1"))
                                      .WillOnce(Return("now"));
  auto date = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_DATE,
                                                 context,
                                                 *io);
  date->Execute();
  ASSERT_EQ(context->buffer_.date.Get().day_number(), Date::GetCurrentTime().day_number());
}


TEST_F(TestInput, shouldIncorrectInputID){
  EXPECT_CALL(*io, Output).Times(6).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(3).WillOnce(Return("123"))
                                      .WillOnce(Return("asdas"))
                                      .WillOnce(Return(""));
  auto date = Factory::CreateState(StatesID::INPUT_ID);
  date->Do(context,*io);
  date->Do(context,*io);
  date->Do(context,*io);
}

TEST_F(TestInput, shouldIncorrectInputPriority){
  EXPECT_CALL(*io, Output).Times(6).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(5).WillOnce(Return("first"))
                                      .WillOnce(Return("second"))
                                      .WillOnce(Return("3"))
                                      .WillOnce(Return("0"))
                                      .WillOnce(Return("AAAAAAAAAAAAAAAAAAAAAAAAa"));
  auto date = Factory::CreateState(StatesID::INPUT_PRIORITY);
  date->Do(context,*io);
  date->Do(context,*io);
  date->Do(context,*io);
  date->Do(context,*io);
  date->Do(context,*io);
}