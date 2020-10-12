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
  EXPECT_CALL(*io, Output).Times(3).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(2).WillOnce(Return("h1yuoas;jfnb1"))
                                      .WillOnce(Return("now"));
  auto date = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_DATE,
                                                 context,
                                                 *io);
  date->Execute();
  ASSERT_EQ(context->buffer_.date.Get().day_number(), Date::GetCurrentTime().day_number());
}


TEST_F(TestInput, shouldCorrectInputID){
  EXPECT_CALL(*io, Output).Times(6).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(3).WillOnce(Return("123"))
                                      .WillOnce(Return("asdas"))
                                      .WillOnce(Return(""));
  auto id = Factory::CreateState(StatesID::INPUT_ID);
  id->Do(context,*io);
  id->Do(context,*io);
  id->Do(context,*io);
}

TEST_F(TestInput, shouldCorrectInputPriority){
  EXPECT_CALL(*io, Output).Times(6).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(5).WillOnce(Return("first"))
                                      .WillOnce(Return("second"))
                                      .WillOnce(Return("3"))
                                      .WillOnce(Return("0"))
                                      .WillOnce(Return("AAAAAAAAAAAAAAAAAAAAAAAAa"));
  auto priority = Factory::CreateState(StatesID::INPUT_PRIORITY);
  priority->Do(context,*io);
  priority->Do(context,*io);
  priority->Do(context,*io);
  priority->Do(context,*io);
  priority->Do(context,*io);
}

TEST_F(TestInput, shouldCorrectInputFileName){
  EXPECT_CALL(*io, Output).Times(3).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(2).WillOnce(Return(""))
      .WillOnce(Return("file"));
  auto filename = Factory::CreateState(StatesID::INPUT_FILE_NAME);
  filename->Do(context,*io);
  filename->Do(context,*io);
}
