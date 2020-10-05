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

TEST_F(TestEditStates, shouldShowAll){
  auto state = Factory::CreateState(StatesID::SHOW_ALL);

  EXPECT_CALL(*io, Output).Times(6).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(3).WillOnce(Return("y"))
                                      .WillOnce(Return("n"))
                                      .WillOnce(Return("12312312"));
  EXPECT_CALL(*service, GetTasks).Times(2).WillRepeatedly(Return(std::vector<TaskServiceDTO>()));
  state->Do(context, *io);
  state->Do(context, *io);
  state->Do(context, *io);
}

TEST_F(TestEditStates, shouldShowToday){
  auto state = Factory::CreateState(StatesID::SHOW_TODAY);

  EXPECT_CALL(*io, Output).Times(6).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(3).WillOnce(Return("y"))
                                      .WillOnce(Return("n"))
                                      .WillOnce(Return("12312312"));
  EXPECT_CALL(*service, GetTodayTasks).Times(2).WillRepeatedly(Return(std::vector<TaskServiceDTO>()));
  state->Do(context, *io);
  state->Do(context, *io);
  state->Do(context, *io);
}

TEST_F(TestEditStates, shouldShowThisWeek){
  auto state = Factory::CreateState(StatesID::SHOW_THIS_WEEK);
  EXPECT_CALL(*io, Output).Times(6).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(3).WillOnce(Return("y"))
      .WillOnce(Return("n"))
      .WillOnce(Return("12312312"));
  EXPECT_CALL(*service, GetWeekTasks).Times(2).WillRepeatedly(Return(std::vector<TaskServiceDTO>()));
  state->Do(context, *io);
  state->Do(context, *io);
  state->Do(context, *io);
}

TEST_F(TestEditStates, shouldShowByName){
  auto state = Factory::CreateState(StatesID::SHOW_BY_NAME);

  EXPECT_CALL(*io, Output).Times(9).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(6).WillOnce(Return("name"))
                                      .WillOnce(Return("y"))
                                      .WillOnce(Return("name3"))
                                      .WillOnce(Return("n"))
                                      .WillOnce(Return("name2"))
                                      .WillOnce(Return("12312312"));
  EXPECT_CALL(*service, GetTasksByName).Times(2).WillRepeatedly(Return(std::vector<TaskServiceDTO>()));
  state->Do(context, *io);
  state->Do(context, *io);
  state->Do(context, *io);
}

TEST_F(TestEditStates, shouldShowByLabel){
  auto state = Factory::CreateState(StatesID::SHOW_BY_LABEL);

  EXPECT_CALL(*io, Output).Times(9).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(6).WillOnce(Return("label"))
      .WillOnce(Return("y"))
      .WillOnce(Return("label3"))
      .WillOnce(Return("n"))
      .WillOnce(Return("label2"))
      .WillOnce(Return("12312312"));
  EXPECT_CALL(*service, GetTasksByLabel).Times(2).WillRepeatedly(Return(std::vector<TaskServiceDTO>()));
  state->Do(context, *io);
  state->Do(context, *io);
  state->Do(context, *io);
}
