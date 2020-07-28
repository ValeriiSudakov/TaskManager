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
}

TEST_F(TestTaskServiceClass, CreateSubTaskWithIncorrectID) {
}

TEST_F(TestTaskServiceClass, DontFindSubtaskByName) {
}

TEST_F(TestTaskServiceClass, RemoveTask){
}

TEST_F(TestTaskServiceClass, SetTaskComplete){
}

TEST_F(TestTaskServiceClass, PostponeDate){
}