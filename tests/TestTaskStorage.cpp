//
// Created by R2D2 on 31.07.2020.
//

#include <gtest/gtest.h>
#include "Memory_Model/Storage/TaskStorage.h"
#include "API/Date/Date.h"

class TestTaskStorage : public ::testing::Test {

 protected:
  virtual void TearDown() {

  }
  virtual void SetUp() {
    auto task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
    ts.AddTask(task.value());
  }
  TaskStorage ts;
};

TEST_F(TestTaskStorage, shouldAddTaskToStorage){
  auto task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto newTask = ts.AddTask(task.value());
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
  auto subtask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto success = ts.AddSubtask(id, subtask.value());
  ASSERT_TRUE(success);
}

TEST_F(TestTaskStorage, shouldntAddSubtaskToStorage){
  auto subtask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  TaskID incorrectID(2121);
  auto success = ts.AddSubtask(incorrectID, subtask.value());
  ASSERT_FALSE(success);
}

TEST_F(TestTaskStorage, shouldRemoveTask){
  ASSERT_TRUE(ts.RemoveTask(TaskID(0)));
}

TEST_F(TestTaskStorage, shouldntRemoveTask){
  ASSERT_FALSE(ts.RemoveTask(TaskID(1242131)));
}