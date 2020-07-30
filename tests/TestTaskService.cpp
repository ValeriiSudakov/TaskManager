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
  Task task = Task::Create("task", "label", Task::Priority::NONE, date);
  ts.AddTask(task, Task::Priority::NONE);
  auto taskTest = ts.GetTasksByName("task", false);
  ASSERT_FALSE(taskTest.empty());
}


TEST_F(TestTaskServiceClass, CreateSubTask) {
  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task, Task::Priority::NONE);

  Task subTask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto taskTest = ts.GetTasksByName("sub task", false);
  ASSERT_TRUE(ts.AddSubtask(taskTest[0].taskID_.GetID(), subTask, Task::Priority::NONE));
}

TEST_F(TestTaskServiceClass, CreateSubTaskWithIncorrectID) {
  TaskService ts;
  TaskIDGenerate idGenerate;

  Task task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task, Task::Priority::NONE);

  Task subTask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  TaskID incorrectID = idGenerate.Generate();
  ASSERT_FALSE(ts.AddSubtask(incorrectID, subTask, Task::Priority::NONE));
}

TEST_F(TestTaskServiceClass, NotFoundTaskByName) {
  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task, Task::Priority::NONE);
  auto resultSearch = ts.GetTasksByName("asf125safs", false);
  ASSERT_TRUE(resultSearch.empty());
}

TEST_F(TestTaskServiceClass, FoundTaskByName) {
  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task, Task::Priority::NONE);
  auto resultSearch = ts.GetTasksByName("asf125safs", false);
  ASSERT_TRUE(resultSearch.empty());
}