//
// Created by R2D2 on 16.07.2020.
//


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "API/Service/TaskServiceClass.h"
#include <iostream>
#include "Repository/RepositoriesFactory/TaskRepositoryFactory.h"
#include "Repository/RepositoryController/TaskRepositoryController.h"
class TestTaskService : public ::testing::Test {

 protected:
  virtual void SetUp() {
    auto factory = std::make_unique<TaskRepositoryFactory>();
    auto controller = std::make_unique<TaskRepositoryController>(std::move(factory));
    ts = std::make_unique<TaskServiceClass>(std::move(controller));
  }
  std::unique_ptr<TaskService> ts;
};

class FakeRepository : public TaskRepository{
  public:
   // MOCK_METHOD(std::unique_ptr<TaskView> , GetTaskView, (), (override));
};

TEST_F(TestTaskService, shouldAddTask) {
  auto dto = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(dto.has_value());
  auto result = ts->AddTask(dto.value());
  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskService, shouldCreateTask) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto taskTest = ts->GetTasksByName("task", false);
  ASSERT_FALSE(taskTest.empty());
}


TEST_F(TestTaskService, shouldCreateSubTask) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());
  auto dto = TaskServiceDTO::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(dto.has_value());
  auto taskTest = ts->GetTasksByName("task", false);
  auto result = ts->AddSubtask(taskTest[0].GetTaskId(), dto.value());
  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskService, shouldntCreateSubTaskWithIncorrectID) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());
  auto dto = TaskServiceDTO::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(dto.has_value());
  TaskID incorrectID(987);
  auto result = ts->AddSubtask(incorrectID, dto.value());
  ASSERT_FALSE(result.success_);
}

TEST_F(TestTaskService, shouldPostpone){
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto now = Date(Date::GetCurrentTime());
  auto task = ts->PostponeTask(TaskID(), now);
  ASSERT_TRUE(task);
  auto findTask = ts->GetTask(TaskID()).value();
  ASSERT_EQ(findTask.GetDate().ToString(), now.ToString());
}

TEST_F(TestTaskService, shouldntPostpone){


  auto task = ts->PostponeTask(TaskID(21321), Date("2019-08-15"));
  ASSERT_FALSE(task);}

TEST_F(TestTaskService, shouldGetByID) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto result = ts->GetTask(TaskID());
  ASSERT_TRUE(result.has_value());
}

TEST_F(TestTaskService, shouldntGetByID) {
  auto result = ts->GetTask(TaskID(1245563));
  ASSERT_FALSE(result.has_value());
}

TEST_F(TestTaskService, shouldFoundTaskByName) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto resultSearch = ts->GetTasksByName("task", false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTaskByNameAndPriority) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto resultSearch = ts->GetTasksByName("task", true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldNotFoundTaskByName) {
  auto resultSearch = ts->GetTasksByName("asf125safs", false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTaskByLabel) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto resultSearch = ts->GetTasksByLabel("label", false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTaskByLabelAndPriority) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto resultSearch = ts->GetTasksByLabel("label", true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldNotFoundTaskByLabel) {
  auto resultSearch = ts->GetTasksByLabel("124rwfsaa21", false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTasks) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto resultSearch = ts->GetTasks( false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTasksByPriority) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto resultSearch = ts->GetTasks(true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldNotFoundTasks) {
  auto resultSearch = ts->GetTasks(false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTodayTasks) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto resultSearch = ts->GetTodayTasks( false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTodayTasksByPriority) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto resultSearch = ts->GetTodayTasks(true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldNotFoundTodayTasks) {
  auto resultSearch = ts->GetTodayTasks(false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundWeekTasks) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto resultSearch = ts->GetWeekTasks( false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundWeekTasksByPriority) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto resultSearch = ts->GetWeekTasks(true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldNotFoundWeekTasks) {

  auto resultSearch = ts->GetWeekTasks(false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTasksPriority) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto resultSearch = ts->GetTasksByPriority(Priority::NONE);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldNotFoundTasksPriority) {
  auto resultSearch = ts->GetTasksByPriority(Priority::FIRST);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldRemoveTask){
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testDTO.has_value());
  ts->AddTask(testDTO.value());

  auto result = ts->RemoveTask(TaskID(0));
  ASSERT_TRUE(result);
}

TEST_F(TestTaskService, shouldntRemoveTask){

  auto result = ts->RemoveTask(TaskID(421));
  ASSERT_FALSE(result);
}

TEST_F(TestTaskService, shouldGetSubtasks){
  auto subtasks = ts->GetSubtask(TaskID(0));
  ASSERT_TRUE(subtasks.empty());

  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ts->AddTask(testDTO.value());

  auto testDTO1 = TaskServiceDTO::Create("sub", "label", Priority::NONE, Date::GetCurrentTime());
  ts->AddSubtask(TaskID(0), testDTO1.value());

  auto subtasks1 = ts->GetSubtask(TaskID(0));
  ASSERT_EQ(subtasks1.size(), 1);
}

TEST_F(TestTaskService, shouldSetComplete) {
  auto testDTO = TaskServiceDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ts->AddTask(testDTO.value());

  ASSERT_TRUE(ts->SetTaskComplete(TaskID(0)));
}

TEST_F(TestTaskService, shouldSave){
  ASSERT_TRUE(ts->Save("savefile.txt"));
}

TEST_F(TestTaskService, shouldLoad){
  ASSERT_TRUE(ts->Load("savefile.txt"));
}
