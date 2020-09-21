//
// Created by R2D2 on 16.07.2020.
//


#include <gtest/gtest.h>
#include "API/TaskServiceClass.h"
#include <iostream>


class TestTaskService : public ::testing::Test {

 protected:
  virtual void SetUp() {
    ts = std::make_unique<TaskServiceClass>(TaskServiceClass::Create());
  }
  std::unique_ptr<TaskService> ts;
};

TEST_F(TestTaskService, shouldAddTask) {
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::Create(task.value().GetName(), task.value().GetLabel(),
                                     task.value().GetPriority(), task.value().GetDueDate());
  auto result = ts->AddTask(dto);
  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskService, shouldCreateTask) {

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  auto taskTest = ts->GetTasksByName("task", false);
  ASSERT_FALSE(taskTest.empty());
}


TEST_F(TestTaskService, shouldCreateSubTask) {

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::Create(subTask.value().GetName(), subTask.value().GetLabel(),
                                     subTask.value().GetPriority(), subTask.value().GetDueDate());
  auto taskTest = ts->GetTasksByName("task", false);
  auto result = ts->AddSubtask(taskTest[0].GetTaskId(), dto);
  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskService, shouldntCreateSubTaskWithIncorrectID) {

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  TaskIDGenerate idGenerate;
  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::Create(subTask.value().GetName(), subTask.value().GetLabel(),
                                     subTask.value().GetPriority(), subTask.value().GetDueDate());
  TaskID incorrectID(987);
  auto result = ts->AddSubtask(incorrectID, dto);
  ASSERT_FALSE(result.success_);
}

TEST_F(TestTaskService, shouldPostpone){

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

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

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  auto result = ts->GetTask(TaskID());
  ASSERT_TRUE(result.has_value());
}

TEST_F(TestTaskService, shouldntGetByID) {


  auto result = ts->GetTask(TaskID(1245563));
  ASSERT_FALSE(result.has_value());
}

TEST_F(TestTaskService, shouldFoundTaskByName) {

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  auto resultSearch = ts->GetTasksByName("task", false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTaskByNameAndPriority) {

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  auto resultSearch = ts->GetTasksByName("task", true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldNotFoundTaskByName) {


  auto resultSearch = ts->GetTasksByName("asf125safs", false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTaskByLabel) {

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  auto resultSearch = ts->GetTasksByLabel("label", false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTaskByLabelAndPriority) {

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  auto resultSearch = ts->GetTasksByLabel("label", true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldNotFoundTaskByLabel) {


  auto resultSearch = ts->GetTasksByLabel("124rwfsaa21", false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTasks) {

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  auto resultSearch = ts->GetTasks( false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTasksByPriority) {

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  auto resultSearch = ts->GetTasks(true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldNotFoundTasks) {


  auto resultSearch = ts->GetTasks(false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTodayTasks) {

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  auto resultSearch = ts->GetTodayTasks( false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTodayTasksByPriority) {

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  auto resultSearch = ts->GetTodayTasks(true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldNotFoundTodayTasks) {

  auto resultSearch = ts->GetTodayTasks(false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundWeekTasks) {

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  auto resultSearch = ts->GetWeekTasks( false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundWeekTasksByPriority) {

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  auto resultSearch = ts->GetWeekTasks(true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldNotFoundWeekTasks) {

  auto resultSearch = ts->GetWeekTasks(false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldFoundTasksPriority) {

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  auto resultSearch = ts->GetTasksByPriority(Priority::NONE);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldNotFoundTasksPriority) {

  auto resultSearch = ts->GetTasksByPriority(Priority::FIRST);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskService, shouldRemoveTask){

  auto test = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto testDTO = TaskDTO::Create(test->GetName(), test->GetLabel(), test->GetPriority(), test->GetDueDate());
  ts->AddTask(testDTO);

  auto result = ts->RemoveTask(TaskID(0));
  ASSERT_TRUE(result);
}

TEST_F(TestTaskService, shouldntRemoveTask){

  auto result = ts->RemoveTask(TaskID(421));
  ASSERT_FALSE(result);
}

TEST_F(TestTaskService, shouldSaveToFile){
  auto result = ts->SaveToFile("SaveFile.txt");
  ASSERT_TRUE(result);
}


TEST_F(TestTaskService, shouldLoadFromFile){
  auto result = ts->LoadFromFile("SaveFile.txt");
  ASSERT_TRUE(result);
}

TEST_F(TestTaskService, shouldntLoadFromFile){
  auto result = ts->LoadFromFile("");
  ASSERT_FALSE(result);
}