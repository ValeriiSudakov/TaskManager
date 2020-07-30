//
// Created by R2D2 on 16.07.2020.
//


#include <gtest/gtest.h>
#include "TaskService.h"
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
  auto taskTest = ts.GetTasksByName("sub task", false);
  ASSERT_TRUE(ts.AddSubtask(taskTest[0].taskID_.GetID(), subTask.value(), Task::Priority::NONE));
}

TEST_F(TestTaskServiceClass, shouldntCreateSubTaskWithIncorrectID) {
  TaskService ts;
  TaskIDGenerate idGenerate;

  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);

  std::optional<Task> subTask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  TaskID incorrectID = idGenerate.Generate();
  ASSERT_FALSE(ts.AddSubtask(incorrectID, subTask.value(), Task::Priority::NONE));
}

TEST_F(TestTaskServiceClass, shouldNotFoundTaskByName) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetTasksByName("asf125safs", false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, shouldFoundTaskByName) {
  TaskService ts;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task.value(), Task::Priority::NONE);
  auto resultSearch = ts.GetTasksByName("asf125safs", false);
  ASSERT_TRUE(resultSearch.empty());
}