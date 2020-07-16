//
// Created by R2D2 on 16.07.2020.
//

#include <gtest/gtest.h>
#include "TaskService.h"
#include <iostream>

class TestTaskServiceClass : public ::testing::Test {

};



TEST_F(TestTaskServiceClass, CreateTask) {

  Date date = TaskService::CreateDate(11, 10, 2020, 3);
  Date date1 = TaskService::CreateDate(22, 1, 2020, 2);

  // CreateTask
  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, date.GetDate());
  ts.AddTask(task,Task::Priority::HIGH);

  auto taskTest = ts.GetTaskByName("task");
  ASSERT_NE(taskTest, nullptr);

  //CreateSubtask
  Task subTask= Task::Create("sub task", "label", Task::Priority::HIGH, date1.GetDate());
  ts.AddSubtask(ts.GetTaskIDByName("task"), subTask, Task::Priority::HIGH);
  auto subtaskTest = ts.GetTaskByName("sub task");
  ASSERT_NE(subtaskTest, nullptr);
}
