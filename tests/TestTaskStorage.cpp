//
// Created by R2D2 on 31.07.2020.
//

#include <gtest/gtest.h>
#include "Memory_Model/TaskStorage.h"
#include "Memory_Model/Date.h"

class TestTaskStorage : public ::testing::Test {

 protected:
  virtual void TearDown() {

  }
  virtual void SetUp() {
    auto task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
    ts.AddTask(task.value(), Task::Priority::NONE);
  }
  TaskStorage ts;
};

TEST_F(TestTaskStorage, shouldAddTaskToStorage){
  auto task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto newTask = ts.AddTask(task.value(), Task::Priority::NONE);
  ASSERT_NE(newTask, nullptr);
}

TEST_F(TestTaskStorage, shoouldGetTaskByID){
  auto temp = ts.GetTask(TaskID(0));
  ASSERT_TRUE(temp.has_value());
}


TEST_F(TestTaskStorage, shoouldntGetTaskByID){
  TaskID id(1252);
  auto temp = ts.GetTask(id);
  ASSERT_FALSE(temp.has_value());
}

TEST_F(TestTaskStorage, shouldAddSubtaskToStorage){
  TaskID id(0);
  auto subtask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto success = ts.AddSubtask(id, subtask.value(), Task::Priority::NONE);
  ASSERT_TRUE(success);
}

TEST_F(TestTaskStorage, shouldntAddSubtaskToStorage){
  auto subtask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  TaskID incorrectID(2121);
  auto success = ts.AddSubtask(incorrectID.GetID(), subtask.value(), Task::Priority::NONE);
  ASSERT_FALSE(success);
}


