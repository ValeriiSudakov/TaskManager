//
// Created by valeriisudakov on 05.10.20.
//


#include <gtest/gtest.h>
#include "Factory/Factory.h"
#include <memory>
#include "mock/Service.h"
#include "mock/InputOutput.h"

using ::testing::Return;
using ::MockService;
using ::MockIO;

class TestEditStates :  public ::testing::Test {
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

TEST_F(TestEditStates, shouldCorrectWorksAddTask){
  auto addTaskState = Factory::CreateState(StatesID::ADD_TASK);

  EXPECT_CALL(*io, Output).Times(5).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(4).WillOnce(Return("name"))
                                      .WillOnce(Return("label"))
                                      .WillOnce(Return("first"))
                                      .WillOnce(Return("now"));
  EXPECT_CALL(*service, AddTask).Times(1).WillOnce(Return(AddTaskResult::Success(TaskID())));
  addTaskState->Do(context, *io);
}

TEST_F(TestEditStates, shouldLoad){
  auto loadState = Factory::CreateState(StatesID::LOAD);

  EXPECT_CALL(*io, Output).Times(1).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(0);
  EXPECT_CALL(*service, Load).Times(1).WillOnce(Return(true));
  loadState->Do(context, *io);
}

TEST_F(TestEditStates, shouldSave){
  auto loadState = Factory::CreateState(StatesID::SAVE);

  EXPECT_CALL(*io, Output).Times(1).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(0);
  EXPECT_CALL(*service, Save).Times(1).WillOnce(Return(true));
  loadState->Do(context, *io);
}