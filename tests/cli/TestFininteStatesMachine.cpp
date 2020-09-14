//
// Created by valeriisudakov on 14.09.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Factory/Factory.h"
#include <memory>
#include "InputOutputLayer.h"

using ::testing::Return;


class TestFiniteStatesMachine :  public ::testing::Test {

};

class MockIO : public InputOutputLayer{
 public:
  MOCK_METHOD(std::string, Input, (), (override));
  MOCK_METHOD(void, Output, (const std::string&), (override));
};



TEST_F(TestFiniteStatesMachine, shouldCorrectChangeStatesFiniteStatesMachine){

  auto context = std::make_shared<Context>(nullptr);
  auto io = std::make_shared<MockIO>();

  // 5 times - "input smth" , 1 time  - "error"
  EXPECT_CALL(*io, Output).Times(6).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(5).WillOnce(Return("name"))
                                       .WillOnce(Return(""))
                                       .WillOnce(Return("Label"))
                                       .WillOnce(Return("first"))
                                       .WillOnce(Return("now"));

  auto stateMachine = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_TASK_PARAMS,
                                                         context,
                                                         io);
  stateMachine->Execute();


}


TEST_F(TestFiniteStatesMachine, shouldCorrectChangeStatesMenuStatesMachine) {

  auto context = std::make_shared<Context>(nullptr);
  auto io = std::make_shared<MockIO>();

  // menus output: 8 +  "input command" * "name, label, priority, date, success" +8
  EXPECT_CALL(*io, Output).Times(22).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(6).WillOnce(Return("add task"))
                                      .WillOnce(Return("name"))
                                      .WillOnce(Return("label"))
                                      .WillOnce(Return("first"))
                                      .WillOnce(Return("now"))
                                      .WillOnce((Return("exit")));

  auto inputNameMachine = Factory::CreateMenuStateMachine(StatesID::BASE_MENU,
                                                        context,
                                                        io);

  inputNameMachine->Execute();
}
