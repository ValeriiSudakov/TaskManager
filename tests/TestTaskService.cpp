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
  try {
    auto taskTest = ts.GetTaskByName("task");
    ASSERT_NE(taskTest, nullptr);
  } catch (const std::exception &ex) {
    std::cout << ex.what();
  }
}


TEST_F(TestTaskServiceClass, CreateSubTask) {

  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, tm());
  ts.AddTask(task, Task::Priority::HIGH);
    Task subTask = Task::Create("sub task", "label", Task::Priority::HIGH, tm());
    ts.AddSubtask("task", subTask, Task::Priority::HIGH);
    auto subtaskTest = ts.GetTaskByName("sub task");
    ASSERT_NE(subtaskTest, nullptr);
}

TEST_F(TestTaskServiceClass, CreateSubTaskWithIncorrectID) {
  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, tm());
  ts.AddTask(task, Task::Priority::HIGH);
  Task subTask = Task::Create("sub task", "label", Task::Priority::HIGH, tm());
  EXPECT_THROW(ts.AddSubtask("sub task312321", subTask,
      Task::Priority::HIGH), std::runtime_error);
}

TEST_F(TestTaskServiceClass, DontFindSubtaskByName) {
  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, tm());
  ts.AddTask(task, Task::Priority::HIGH);
  Task subTask = Task::Create("sub task", "label", Task::Priority::HIGH, tm());
  ts.AddSubtask("task", subTask, Task::Priority::HIGH);
  EXPECT_THROW(ts.GetTaskByName("sub task213"), std::runtime_error);
}

TEST_F(TestTaskServiceClass, RemoveTask){
  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  ts.AddTask(task, Task::Priority::HIGH);
  tm tm1 = Date::GetCurrentTime();
  tm1.tm_mday++;
  ts.PostponeDate("task", tm1);
  ts.RemoveTask("task");
  EXPECT_THROW(ts.GetTaskByName("task"),std::runtime_error);
}

TEST_F(TestTaskServiceClass, SetTaskComplete){
  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  ts.AddTask(task, Task::Priority::HIGH);
  EXPECT_FALSE(ts.GetTaskByName("task").lock()->IsComplete());

  Task subTask = Task::Create("sub task", "label", Task::Priority::HIGH, tm());
  ts.AddSubtask("task", subTask, Task::Priority::HIGH);
  EXPECT_FALSE(ts.GetTaskByName("sub task").lock()->IsComplete());

  ts.SetTaskComplete("task");
  EXPECT_TRUE(ts.GetTaskByName("task").lock()->IsComplete());
  EXPECT_TRUE(ts.GetTaskByName("sub task").lock()->IsComplete());
}

TEST_F(TestTaskServiceClass, PostponeDate){
  TaskService ts;
  tm date = Date::GetCurrentTime();
  Task task = Task::Create("task", "label", Task::Priority::HIGH, date);
  ts.AddTask(task, Task::Priority::HIGH);

  date.tm_mday++;
  ts.PostponeDate("task", date);

  tm taskDate = ts.GetTaskByName("task").lock()->GetTaskDueDate();
  ASSERT_EQ(mktime(&taskDate), mktime(&date));
}