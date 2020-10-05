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

  EXPECT_CALL(*io, Output).Times(2).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("y"));
  EXPECT_CALL(*service, GetTasks).Times(1).WillOnce(Return(std::vector<TaskServiceDTO>()));
  state->Do(context, *io);
}

TEST_F(TestEditStates, shouldShowToday){
  auto state = Factory::CreateState(StatesID::SHOW_TODAY);

  EXPECT_CALL(*io, Output).Times(2).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("y"));
  EXPECT_CALL(*service, GetTodayTasks).Times(1).WillOnce(Return(std::vector<TaskServiceDTO>()));
  state->Do(context, *io);
}

TEST_F(TestEditStates, shouldShowThisWeek){
  auto state = Factory::CreateState(StatesID::SHOW_THIS_WEEK);

  EXPECT_CALL(*io, Output).Times(2).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("y"));
  EXPECT_CALL(*service, GetWeekTasks).Times(1).WillOnce(Return(std::vector<TaskServiceDTO>()));
  state->Do(context, *io);
}

TEST_F(TestEditStates, shouldShowByName){
  auto state = Factory::CreateState(StatesID::SHOW_BY_NAME);

  EXPECT_CALL(*io, Output).Times(3).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(2).WillOnce(Return("name"))
                                      .WillOnce(Return("y"));
  EXPECT_CALL(*service, GetTasksByName).Times(1).WillOnce(Return(std::vector<TaskServiceDTO>()));
  state->Do(context, *io);
}

TEST_F(TestEditStates, shouldShowByLabel){
  auto state = Factory::CreateState(StatesID::SHOW_BY_LABEL);

  EXPECT_CALL(*io, Output).Times(3).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(2).WillOnce(Return("label"))
      .WillOnce(Return("y"));
  EXPECT_CALL(*service, GetTasksByLabel).Times(1).WillOnce(Return(std::vector<TaskServiceDTO>()));
  state->Do(context, *io);
}
