//
// Created by R2D2 on 16.07.2020.
//

#include <gtest/gtest.h>
#include "TaskService.h"
#include <iostream>

class TestTaskServiceClass : public ::testing::Test {

};

TEST_F(TestTaskServiceClass, CreateTask) {
  // CreateTask
  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, tm());
  ts.AddTask(task,Task::Priority::HIGH);

  auto taskTest = ts.GetTaskByName("task");
  ASSERT_NE(taskTest, nullptr);

  //CreateSubtask
  Task subTask= Task::Create("sub task", "label", Task::Priority::HIGH, tm());
  ts.AddSubtask(ts.GetTaskIDByName("task"), subTask, Task::Priority::HIGH);
  auto subtaskTest = ts.GetTaskByName("sub task");
  ASSERT_NE(subtaskTest, nullptr);
}
