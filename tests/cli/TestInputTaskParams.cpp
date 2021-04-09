//
// Created by valeriisudakov on 14.09.20.
//


#include "Factory.h"
#include <gtest/gtest.h>
#include <memory>
#include "mock/Service.h"
#include "mock/InputOutput.h"

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

using ::testing::Return;


TEST_F(TestInput, shouldBeCorrectInputName){
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

TEST_F(TestInput, shouldCorrectInputLabel){
  EXPECT_CALL(*io, Output).Times(3).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(2).WillOnce(Return(""))
      .WillOnce(Return("label"));

  auto label = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_LABEL,
                                                 context,
                                                  *io);
  label->Execute();
  ASSERT_EQ(context->buffer_.label, "label");
}


TEST_F(TestInput, shouldCorrectInputDatetime){
  EXPECT_CALL(*io, Output).Times(1).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("now"));
  auto date = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_DATE,
                                                  context,
                                                  *io);
  date->Execute();
  ASSERT_EQ(context->buffer_.date.Get().day_number(), Date::GetCurrentTime().day_number());
}
