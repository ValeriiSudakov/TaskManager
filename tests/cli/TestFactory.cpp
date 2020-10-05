//
// Created by valeriisudakov on 14.09.20.
//

#include "Factory/Factory.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "InputOutputConsoleLayer.h"
#include "API/TaskService.h"

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

class TestFactory :  public ::testing::Test {
 protected:
  virtual void SetUp() override{
    service = std::make_unique<MockService>();
    context = std::make_shared<Context>(*service);
    io = std::make_shared<InputOutputConsoleLayer>();
  }

  std::shared_ptr<Context> context;
  std::unique_ptr<MockService> service;
  std::shared_ptr<InputOutputLayer> io;

};

TEST_F(TestFactory, shouldCorrectCreateStates){
  auto addTask = Factory::CreateState(StatesID::ADD_TASK);
  ASSERT_EQ(addTask->GetStateID(), StatesID::ADD_TASK);

  auto addSubtask = Factory::CreateState(StatesID::ADD_SUBTASK);
  ASSERT_EQ(addSubtask->GetStateID(), StatesID::ADD_SUBTASK);

  auto postpone = Factory::CreateState(StatesID::POSTPONE);
  ASSERT_EQ(postpone->GetStateID(), StatesID::POSTPONE);

  auto complete = Factory::CreateState(StatesID::COMPLETE);
  ASSERT_EQ(complete->GetStateID(), StatesID::COMPLETE);

  auto remove = Factory::CreateState(StatesID::DELETE);
  ASSERT_EQ(remove->GetStateID(), StatesID::DELETE);

  auto inputName = Factory::CreateState(StatesID::INPUT_NAME);
  ASSERT_EQ(inputName->GetStateID(), StatesID::INPUT_NAME);

  auto inputLabel = Factory::CreateState(StatesID::INPUT_LABEL);
  ASSERT_EQ(inputLabel->GetStateID(), StatesID::INPUT_LABEL);

  auto inputDate = Factory::CreateState(StatesID::INPUT_DATE);
  ASSERT_EQ(inputDate->GetStateID(), StatesID::INPUT_DATE);

  auto inputPriority = Factory::CreateState(StatesID::INPUT_PRIORITY);
  ASSERT_EQ(inputPriority->GetStateID(), StatesID::INPUT_PRIORITY);

  auto inputTask = Factory::CreateState(StatesID::INPUT_TASK);
  ASSERT_EQ(inputTask->GetStateID(), StatesID::INPUT_TASK);

  auto baseMenu = Factory::CreateState(StatesID::BASE_MENU);
  ASSERT_EQ(baseMenu->GetStateID(), StatesID::BASE_MENU);

  auto continueMenu = Factory::CreateState(StatesID::CONTINUE_MENU);
  ASSERT_EQ(continueMenu->GetStateID(), StatesID::CONTINUE_MENU);

  auto showAll = Factory::CreateState(StatesID::SHOW_ALL);
  ASSERT_EQ(showAll->GetStateID(), StatesID::SHOW_ALL);

  auto showByID = Factory::CreateState(StatesID::SHOW_BY_ID);
  ASSERT_EQ(showByID->GetStateID(), StatesID::SHOW_BY_ID);

  auto showByLabel = Factory::CreateState(StatesID::SHOW_BY_LABEL);
  ASSERT_EQ(showByLabel->GetStateID(), StatesID::SHOW_BY_LABEL);

  auto showByName = Factory::CreateState(StatesID::SHOW_BY_NAME);
  ASSERT_EQ(showByName->GetStateID(), StatesID::SHOW_BY_NAME);

  auto showToday = Factory::CreateState(StatesID::SHOW_TODAY);
  ASSERT_EQ(showToday->GetStateID(), StatesID::SHOW_TODAY);

  auto showWeek = Factory::CreateState(StatesID::SHOW_THIS_WEEK);
  ASSERT_EQ(showWeek->GetStateID(), StatesID::SHOW_THIS_WEEK);

  auto Exit = Factory::CreateState(StatesID::EXIT);
  ASSERT_EQ(Exit, nullptr);
}

TEST_F(TestFactory, shouldCorrectCreateAfterMenu) {

  auto show = Factory::CreateAfterMenuState(StatesID::SHOW, context, *io);
  ASSERT_NE(show, nullptr);

  auto edit = Factory::CreateAfterMenuState(StatesID::EDIT, context, *io);
  ASSERT_NE(edit, nullptr);

}

TEST_F(TestFactory, shouldCorrectCreateMenu){

  auto baseMenu = Factory::CreateMenuStateMachine(StatesID::BASE_MENU, context, *io);
  ASSERT_NE(baseMenu, nullptr);

  auto continueMenu = Factory::CreateMenuStateMachine(StatesID::CONTINUE_MENU, context, *io);
  ASSERT_NE(continueMenu, nullptr);

}

TEST_F(TestFactory, shouldCorrectCreate){

  auto inputName = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_NAME, context, *io);
  ASSERT_NE(inputName, nullptr);

  auto inputLabel = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_LABEL, context, *io);
  ASSERT_NE(inputName, nullptr);

  auto inputID = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_ID, context, *io);
  ASSERT_NE(inputID, nullptr);

  auto inputDate = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_DATE, context, *io);
  ASSERT_NE(inputDate, nullptr);

  auto postpone = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::POSTPONE, context, *io);
  ASSERT_NE(postpone, nullptr);

  auto taskParams = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_TASK_PARAMS, context, *io);
  ASSERT_NE(taskParams, nullptr);

  auto subtaskParams = Factory::CreateFiniteStatesMachine(FiniteStateMachineID::INPUT_SUBTASK_PARAMS, context, *io);
  ASSERT_NE(subtaskParams, nullptr);
}