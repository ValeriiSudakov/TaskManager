//
// Created by R2D2 on 16.07.2020.
//

#include <gtest/gtest.h>
#include "TaskService.h"
#include <iostream>

class TestTaskServiceClass : public ::testing::Test {

};



TEST_F(TestTaskServiceClass, CreateTask) {

  tm date = Date::CreateDate(11, 10, 2020, 3);

  // CreateTask
  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, date);
  ts.AddTask(task, Task::Priority::HIGH);
  auto taskTest = ts.taskView.GetTasksByName("task", false);
  ASSERT_FALSE(taskTest.empty());
}


TEST_F(TestTaskServiceClass, CreateSubTask) {
  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  ts.AddTask(task, Task::Priority::HIGH);

  Task subTask = Task::Create("sub task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  auto resultSearch = ts.taskView.GetTasksByName("task", false);
  ASSERT_TRUE(ts.AddSubtask(resultSearch[0].taskID, subTask, Task::Priority::HIGH));
}

TEST_F(TestTaskServiceClass, CreateSubTaskWithIncorrectID) {
  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  ts.AddTask(task, Task::Priority::HIGH);

  Task subTask = Task::Create("sub task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  TaskID incorrectID(4);
  ASSERT_FALSE(ts.AddSubtask(incorrectID, subTask, Task::Priority::HIGH));
}

TEST_F(TestTaskServiceClass, NotFoundTaskByName) {
  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  ts.AddTask(task, Task::Priority::HIGH);
  auto resultSearch = ts.taskView.GetTasksByName("asf125safs", false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, FoundTaskByName) {
  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  ts.AddTask(task, Task::Priority::HIGH);
  auto resultSearch = ts.taskView.GetTasksByName("asf125safs", false);
  ASSERT_TRUE(resultSearch.empty());
}
