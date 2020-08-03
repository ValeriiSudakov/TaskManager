//
// Created by R2D2 on 16.07.2020.
//


#include <gtest/gtest.h>
#include "API/TaskService.h"
#include <iostream>

class TestTaskServiceClass : public ::testing::Test {

};



TEST_F(TestTaskServiceClass, shouldCreateTask) {
  // CreateTask
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto taskTest = ts.GetTasksByName("task", false);
  ASSERT_FALSE(taskTest.empty());
}


TEST_F(TestTaskServiceClass, shouldCreateSubTask) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);

  std::optional<Task> subTask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto taskTest = ts.GetTasksByName("task", false);
  ASSERT_TRUE(ts.AddSubtask(taskTest[0].taskID_.GetID(), subTask.value(), Task::Priority::NONE));
}

TEST_F(TestTaskServiceClass, shouldntCreateSubTaskWithIncorrectID) {
  TaskService ts;
  TaskIDGenerate idGenerate;

  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);

  std::optional<Task> subTask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  TaskID incorrectID(987);
  ASSERT_FALSE(ts.AddSubtask(incorrectID, subTask.value(), Task::Priority::NONE));
}


TEST_F(TestTaskServiceClass, shouldFoundTaskByName) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetTasksByName("task", false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTaskByNameAndPriority) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetTasksByName("task", true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldNotFoundTaskByName) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetTasksByName("asf125safs", false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTaskByLabel) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetTasksByLabel("label", false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTaskByLabelAndPriority) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetTasksByLabel("label", true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldNotFoundTaskByLabel) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetTasksByLabel("124rwfsaa21", false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTasks) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetTasks( false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTasksByPriority) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetTasks(true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldNotFoundTasks) {
  TaskService ts;
  auto resultSearch = ts.GetTasks(false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTodayTasks) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetTodayTasks( false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTodayTasksByPriority) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetTodayTasks(true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldNotFoundTodayTasks) {
  TaskService ts;
  auto resultSearch = ts.GetTodayTasks(false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundWeekTasks) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetWeekTasks( false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundWeekTasksByPriority) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetWeekTasks(true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldNotFoundWeekTasks) {
  TaskService ts;
  auto resultSearch = ts.GetWeekTasks(false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTasksPriority) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetTasksByPriority(Task::Priority::NONE);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldNotFoundTasksPriority) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetTasksByPriority(Task::Priority::FIRST);
  ASSERT_TRUE(resultSearch.empty());
}