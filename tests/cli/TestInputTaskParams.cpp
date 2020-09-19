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
  MOCK_METHOD(AddTaskResult,          AddTask,            (const TaskDTO&), (override));
  MOCK_METHOD(AddTaskResult,          AddSubtask,         (const TaskID&, const TaskDTO&), (override));
  MOCK_METHOD(bool,                   RemoveTask,         (const TaskID&), (override));
  MOCK_METHOD(bool,                   PostponeTask,       (const TaskID&, const Date&), (override));
  MOCK_METHOD(bool,                   SetTaskComplete,    (const TaskID&), (override));
  MOCK_METHOD(std::optional<TaskDTO>, GetTask,            (const TaskID&), (const override));
  MOCK_METHOD(std::vector<TaskDTO>,   GetSubtask,         (const TaskID&), (const override));
  MOCK_METHOD(std::vector<TaskDTO>,   GetTasks,           (bool), (const override));
  MOCK_METHOD(std::vector<TaskDTO>,   GetTodayTasks,      (bool), (const override));
  MOCK_METHOD(std::vector<TaskDTO>,   GetWeekTasks,       (bool), (const override));
  MOCK_METHOD(std::vector<TaskDTO>,   GetTasksByName,     (const std::string&, bool), (const override));
  MOCK_METHOD(std::vector<TaskDTO>,   GetTasksByLabel,    (const std::string&, bool), (const override));
  MOCK_METHOD(std::vector<TaskDTO>,   GetTasksByPriority, (const Priority&), (const override));

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

  auto context = std::make_shared<Context>(*std::make_unique<TaskServiceClass>(TaskServiceClass::Create()));
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


TEST_F(TestInput, shouldCorrectInputDate){
  EXPECT_CALL(*io, Output).Times(1).WillRepeatedly(Return());
  EXPECT_CALL(*io, Input).Times(1).WillOnce(Return("now"));
  auto date = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_DATE,
                                                  context,
                                                  *io);
  date->Execute();
  ASSERT_EQ(context->buffer_.date.Get().day_number(), Date::GetCurrentTime().day_number());
}
