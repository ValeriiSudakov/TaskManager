//
// Created by valeriisudakov on 31.07.2020.
//

#include <gtest/gtest.h>
#include "TaskStorageClass.h"
#include "Date.h"

class TestTaskStorage : public ::testing::Test {

 protected:
  virtual void TearDown() {

  }
  virtual void SetUp() {
    auto task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
    ts.AddTask(TaskEntity(task.value(), generator.Generate()));
  }
  TaskStorageClass ts;
  TaskIDGenerate generator;
};

TEST_F(TestTaskStorage, shouldAddTaskToStorage){
  auto task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto newTask = ts.AddTask(TaskEntity(task.value(), generator.Generate()));
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

TEST_F(TestTaskStorage, shouldRemoveTask){
  ASSERT_TRUE(ts.RemoveTask(TaskID(0)));
}

TEST_F(TestTaskStorage, shouldntRemoveTask){
  ASSERT_FALSE(ts.RemoveTask(TaskID(1242131)));
}