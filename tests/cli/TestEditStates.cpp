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
    auto task = TaskServiceDTO::Create("name", "label", Priority::SECOND,
                                       Date::GetCurrentTime(), false, TaskID(0));
    context->tasks_.push_back(task.value());
  }

 protected:
  std::shared_ptr<MockIO> io;
  std::shared_ptr<Context> context;
  std::unique_ptr<MockService> service;
};

TEST_F(TestEditStates, shouldAddTask){
  auto addTaskState = Factory::CreateState(StatesID::ADD_TASK);

  EXPECT_CALL(*io, Output).Times(5).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(4).WillOnce(Return("name"))
                                      .WillOnce(Return("label"))
                                      .WillOnce(Return("first"))
                                      .WillOnce(Return("now"));
  EXPECT_CALL(*service, AddTask).Times(1).WillOnce(Return(AddTaskResult::Success(TaskID())));

  auto result = addTaskState->Do(context, *io);
  ASSERT_EQ(result, StateOperationResult::SUCCESS);
}

TEST_F(TestEditStates, shouldntAddTask){
  auto addTaskState = Factory::CreateState(StatesID::ADD_TASK);

  EXPECT_CALL(*io, Output).Times(5).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(4).WillOnce(Return("name"))
      .WillOnce(Return("label"))
      .WillOnce(Return("first"))
      .WillOnce(Return("now"));
  EXPECT_CALL(*service, AddTask).Times(1)
      .WillOnce(Return(AddTaskResult::Failed(AddTaskResult::ErrorType::NOT_ENOUGH_FREE_MEMORY)));

  auto result = addTaskState->Do(context, *io);
  ASSERT_EQ(result, StateOperationResult::FAIL);
}

TEST_F(TestEditStates, shouldLoad){
  auto loadState = Factory::CreateState(StatesID::LOAD);

  EXPECT_CALL(*io, Output).Times(2).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("file.txt"));
  EXPECT_CALL(*service, Load).Times(1).WillOnce(Return(true));

  auto result = loadState->Do(context, *io);
  ASSERT_EQ(result, StateOperationResult::SUCCESS);
}

TEST_F(TestEditStates, shouldntLoad){
  auto loadState = Factory::CreateState(StatesID::LOAD);

  EXPECT_CALL(*io, Output).Times(2).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("file.txt"));
  EXPECT_CALL(*service, Load).Times(1).WillOnce(Return(false));

  auto result = loadState->Do(context, *io);
  ASSERT_EQ(result, StateOperationResult::SUCCESS);
}

TEST_F(TestEditStates, shouldSave){
  auto loadState = Factory::CreateState(StatesID::SAVE);

  EXPECT_CALL(*io, Output).Times(2).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("file.txt"));
  EXPECT_CALL(*service, Save).Times(1).WillOnce(Return(true));
  loadState->Do(context, *io);
}

TEST_F(TestEditStates, shoulntdSave){
  auto loadState = Factory::CreateState(StatesID::SAVE);

  EXPECT_CALL(*io, Output).Times(2).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("file.txt"));
  EXPECT_CALL(*service, Save).Times(1).WillOnce(Return(false));
  loadState->Do(context, *io);
}

TEST_F(TestEditStates, shouldntAddSubtask){
  auto addSubtaskState = Factory::CreateState(StatesID::ADD_SUBTASK);

  EXPECT_CALL(*io, Output).Times(6).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(5).WillOnce(Return("0"))
      .WillOnce(Return("name"))
      .WillOnce(Return("label"))
      .WillOnce(Return("first"))
      .WillOnce(Return("now"));
  EXPECT_CALL(*service, AddSubtask).Times(1)
      .WillOnce(Return(AddTaskResult::Failed(AddTaskResult::ErrorType::NOT_ENOUGH_FREE_MEMORY)));

  auto result = addSubtaskState->Do(context, *io);
  ASSERT_EQ(result, StateOperationResult::FAIL);
}

TEST_F(TestEditStates, shouldAddSubtask){
  auto addSubtaskState = Factory::CreateState(StatesID::ADD_SUBTASK);

  EXPECT_CALL(*io, Output).Times(6).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(5).WillOnce(Return("0"))
      .WillOnce(Return("name"))
      .WillOnce(Return("label"))
      .WillOnce(Return("first"))
      .WillOnce(Return("now"));
  EXPECT_CALL(*service, AddSubtask).Times(1).WillOnce(Return(AddTaskResult::Success(TaskID())));

  auto result = addSubtaskState->Do(context, *io);
  ASSERT_EQ(result, StateOperationResult::SUCCESS);
}

TEST_F(TestEditStates, shouldRemoveTask){
  auto remove = Factory::CreateState(StatesID::DELETE);

  EXPECT_CALL(*io, Output).Times(2).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("0"));
  EXPECT_CALL(*service, RemoveTask).Times(1).WillOnce(Return(true));

  auto result = remove->Do(context, *io);
  ASSERT_EQ(result, StateOperationResult::SUCCESS);
}

TEST_F(TestEditStates, shouldntRemoveTask){
  auto remove = Factory::CreateState(StatesID::DELETE);

  EXPECT_CALL(*io, Output).Times(2).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("0"));
  EXPECT_CALL(*service, RemoveTask).Times(1).WillOnce(Return(false));

  auto result = remove->Do(context, *io);
  ASSERT_EQ(result, StateOperationResult::FAIL);
}

TEST_F(TestEditStates, shouldCompleteTask){
  auto complete = Factory::CreateState(StatesID::COMPLETE);

  EXPECT_CALL(*io, Output).Times(2).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("0"));
  EXPECT_CALL(*service, SetTaskComplete).Times(1).WillOnce(Return(true));

  auto result = complete->Do(context, *io);
  ASSERT_EQ(result, StateOperationResult::SUCCESS);
}

TEST_F(TestEditStates, shouldntCompleteTask){
  auto complete = Factory::CreateState(StatesID::COMPLETE);

  EXPECT_CALL(*io, Output).Times(2).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("0"));
  EXPECT_CALL(*service, SetTaskComplete).Times(1).WillOnce(Return(false));

  auto result = complete->Do(context, *io);
  ASSERT_EQ(result, StateOperationResult::FAIL);
}

TEST_F(TestEditStates, shouldPostponeTask){
  auto postpone = Factory::CreateState(StatesID::POSTPONE);

  EXPECT_CALL(*io, Output).Times(3).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(2).WillOnce(Return("0"))
      .WillOnce(Return("now"));
  EXPECT_CALL(*service, PostponeTask).Times(1).WillOnce(Return(true));

  auto result = postpone->Do(context, *io);
  ASSERT_EQ(result, StateOperationResult::SUCCESS);
}

TEST_F(TestEditStates, shouldntPostponeTask){
  auto postpone = Factory::CreateState(StatesID::POSTPONE);

  EXPECT_CALL(*io, Output).Times(3).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(2).WillOnce(Return("0"))
      .WillOnce(Return("now"));
  EXPECT_CALL(*service, PostponeTask).Times(1).WillOnce(Return(false));

  auto result = postpone->Do(context, *io);
  ASSERT_EQ(result, StateOperationResult::FAIL);
}
