//
// Created by R2D2 on 16.07.2020.
//


#include <gtest/gtest.h>
#include "API/TaskService.h"
#include <iostream>

class TestTaskServiceClass : public ::testing::Test {

 protected:
  virtual void TearDown() {

  }
  virtual void SetUp() {
    std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
    TaskDTO newTask(task.value(), false, TaskID());
    ts.AddTask(newTask, Task::Priority::NONE);
  }
  TaskService ts;
};

TEST_F(TestTaskServiceClass, shouldAddTask) {
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  TaskDTO newTask(task.value(), false, TaskID());
  auto result = ts.AddTask(newTask, Task::Priority::NONE);
  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskServiceClass, shouldCreateTask) {
  // CreateTask
  auto taskTest = ts.GetTasksByName("task", false);
  ASSERT_FALSE(taskTest.empty());
}


TEST_F(TestTaskServiceClass, shouldCreateSubTask) {
  std::optional<Task> subTask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  TaskDTO newTask(subTask.value(), false, TaskID());
  auto taskTest = ts.GetTasksByName("task", false);
  auto result = ts.AddSubtask(taskTest[0].GetTaskId().GetID(), newTask, Task::Priority::NONE);
  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskServiceClass, shouldntCreateSubTaskWithIncorrectID) {
  TaskIDGenerate idGenerate;
  std::optional<Task> subTask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  TaskDTO newTask(subTask.value(), false, TaskID());
  TaskID incorrectID(987);
  auto result = ts.AddSubtask(incorrectID, newTask, Task::Priority::NONE);
  ASSERT_FALSE(result.success_);
}


TEST_F(TestTaskServiceClass, shouldFoundTaskByName) {
  auto resultSearch = ts.GetTasksByName("task", false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTaskByNameAndPriority) {
  auto resultSearch = ts.GetTasksByName("task", true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldNotFoundTaskByName) {
  auto resultSearch = ts.GetTasksByName("asf125safs", false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTaskByLabel) {
  auto resultSearch = ts.GetTasksByLabel("label", false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTaskByLabelAndPriority) {
  auto resultSearch = ts.GetTasksByLabel("label", true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldNotFoundTaskByLabel) {
  auto resultSearch = ts.GetTasksByLabel("124rwfsaa21", false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTasks) {
  auto resultSearch = ts.GetTasks( false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTasksByPriority) {
  auto resultSearch = ts.GetTasks(true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldNotFoundTasks) {
  TaskService ts;
  auto resultSearch = ts.GetTasks(false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTodayTasks) {
  auto resultSearch = ts.GetTodayTasks( false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTodayTasksByPriority) {
  auto resultSearch = ts.GetTodayTasks(true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldNotFoundTodayTasks) {
  TaskService ts;
  auto resultSearch = ts.GetTodayTasks(false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundWeekTasks) {
  auto resultSearch = ts.GetWeekTasks( false);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundWeekTasksByPriority) {
  auto resultSearch = ts.GetWeekTasks(true);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldNotFoundWeekTasks) {
  TaskService ts;
  auto resultSearch = ts.GetWeekTasks(false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTasksPriority) {
  auto resultSearch = ts.GetTasksByPriority(Task::Priority::NONE);
  ASSERT_FALSE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldNotFoundTasksPriority) {
  auto resultSearch = ts.GetTasksByPriority(Task::Priority::FIRST);
  ASSERT_TRUE(resultSearch.empty());
}
