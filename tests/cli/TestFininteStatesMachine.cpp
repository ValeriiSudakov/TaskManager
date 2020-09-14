//
// Created by valeriisudakov on 14.09.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Factory/Factory.h"
#include <memory>
#include "InputOutputLayer.h"

using ::testing::Return;


class MockIO : public InputOutputLayer{
 public:
  MOCK_METHOD(std::string, Input, (), (override));
  MOCK_METHOD(void, Output, (const std::string&), (override));
};

class TestFiniteStatesMachine :  public ::testing::Test {

};

TEST_F(TestFiniteStatesMachine, shouldCorrectChangeStatesFiniteStatesMachine){
  // 5 times - "input smth" , 1 time  - "error"

  std::shared_ptr<MockIO> io = std::make_shared<MockIO>();
  std::shared_ptr<Context> context = std::make_shared<Context>(nullptr);
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

  std::shared_ptr<MockIO> io = std::make_shared<MockIO>();
  std::shared_ptr<Context> context = std::make_shared<Context>(nullptr);
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
                                                        *io);

  inputNameMachine->Execute();
}
