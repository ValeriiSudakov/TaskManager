//
// Created by valeriisudakov on 14.09.20.
//


#include "Factory/Factory.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "InputOutputLayer.h"


class TestInput :  public ::testing::Test {

};

using ::testing::Return;

class MockIO : public InputOutputLayer{
 public:
  MOCK_METHOD(std::string, Input, (), (override));
  MOCK_METHOD(void, Output, (const std::string&), (override));
};


TEST_F(TestInput, shouldCorrectInputName){
  auto io = std::make_shared<MockIO>();
  EXPECT_CALL(*io, Output).Times(3).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(2).WillOnce(Return(""))
                                      .WillOnce(Return("name"));

  auto context = std::make_shared<Context>(nullptr);
  auto name = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_NAME,
                                                 context,
                                                 *io);
  name->Execute();
}

TEST_F(TestInput, shouldCorrectInputLabel){
  auto io = std::make_shared<MockIO>();
  EXPECT_CALL(*io, Output).Times(3).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(2).WillOnce(Return(""))
      .WillOnce(Return("label"));

  auto context = std::make_shared<Context>(nullptr);
  auto label = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_LABEL,
                                                 context,
                                                  *io);
  label->Execute();
}


TEST_F(TestInput, shouldCorrectInputDate){
  auto io = std::make_shared<MockIO>();
  EXPECT_CALL(*io, Output).Times(1).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("now"));

  auto context = std::make_shared<Context>(nullptr);
  auto date = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_DATE,
                                                  context,
                                                  *io);
  date->Execute();
}