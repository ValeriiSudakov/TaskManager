//
// Created by valeriisudakov on 14.09.20.
//


#include "Factory/Factory.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "InputOutputLayer.h"


class MockService : public TaskService{
 public:
  MOCK_METHOD(AddTaskResult,                 AddTask,            (const TaskServiceDTO&), (override));
  MOCK_METHOD(AddTaskResult,                 AddSubtask,         (const TaskID&, const TaskServiceDTO&), (override));
  MOCK_METHOD(bool,                          RemoveTask,         (const TaskID&), (override));
  MOCK_METHOD(bool,                          PostponeTask,       (const TaskID&, const Date&), (override));
  MOCK_METHOD(bool,                          SetTaskComplete,    (const TaskID&), (override));
  MOCK_METHOD(bool,                          Save, (), (override));
  MOCK_METHOD(bool,                          Load, (), (override));
  MOCK_METHOD(std::optional<TaskServiceDTO>, GetTask, (const TaskID&), (const override));
  MOCK_METHOD(std::vector<TaskServiceDTO>,   GetSubtask, (const TaskID&), (const override));
  MOCK_METHOD(std::vector<TaskServiceDTO>,   GetTasks, (bool), (const override));
  MOCK_METHOD(std::vector<TaskServiceDTO>,   GetTodayTasks, (bool), (const override));
  MOCK_METHOD(std::vector<TaskServiceDTO>,   GetWeekTasks, (bool), (const override));
  MOCK_METHOD(std::vector<TaskServiceDTO>,   GetTasksByName, (const std::string&, bool), (const override));
  MOCK_METHOD(std::vector<TaskServiceDTO>,   GetTasksByLabel, (const std::string&, bool), (const override));
  MOCK_METHOD(std::vector<TaskServiceDTO>,   GetTasksByPriority, (const Priority&), (const override));
};

class MockIO : public InputOutputLayer{
 public:
  MOCK_METHOD(std::string, Input, (), (override));
  MOCK_METHOD(void, Output, (const std::string&), (override));
};

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


TEST_F(TestInput, shouldCorrectInputName){
  EXPECT_CALL(*io, Output).Times(3).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(2).WillOnce(Return(""))
                                      .WillOnce(Return("name"));

  auto context = std::make_shared<Context>(*std::make_unique<TaskServiceClass>(TaskServiceUtils::GetRepositoryFactory()));
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