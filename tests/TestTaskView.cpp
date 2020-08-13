//
// Created by R2D2 on 28.07.2020.
//

#include <gtest/gtest.h>
#include "API/TaskService.h"
#include <iostream>

class TestTaskViewClass : public ::testing::Test {

 protected:
  TaskView tv;
  TaskIDGenerate taskIDGenerate;
};

TEST_F(TestTaskViewClass, shouldAddTask){
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);
  auto result = tv.GetTasks();
  ASSERT_FALSE(result.empty());
}

TEST_F(TestTaskViewClass, shouldGetData){
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);
  auto resultByName = tv.GetTasksByName("task");
  ASSERT_FALSE(resultByName.empty());

  auto resultByLabel = tv.GetTasksByLabel("label");
  ASSERT_FALSE(resultByLabel.empty());

  auto resultByPriority = tv.GetTasksByPriority(Priority::NONE);
  ASSERT_FALSE(resultByPriority.empty());

  auto resultForToday = tv.GetTodayTasks();
  ASSERT_FALSE(resultForToday.empty());
}

TEST_F(TestTaskViewClass, shouldntGetData){
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);
  auto resultByName = tv.GetTasksByName("");
  ASSERT_TRUE(resultByName.empty());

  auto resultByLabel = tv.GetTasksByLabel("");
  ASSERT_TRUE(resultByLabel.empty());

  auto resultByPriority = tv.GetTasksByPriority(Priority::FIRST);
  ASSERT_TRUE(resultByPriority.empty());
}

TEST_F(TestTaskViewClass, shouldGetCorrectTaskData){
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);
  TaskIDGenerate taskIDGenerate;
  TaskID id(taskIDGenerate.Generate());
  auto result = tv.GetTasks();
  ASSERT_FALSE(result.empty());

  ASSERT_FALSE(result[0].IsComplete());
  ASSERT_EQ(result[0].GetId(), id);
  ASSERT_EQ(result[0].GetPriority(), Priority::NONE);
  ASSERT_EQ(result[0].GetLabel(), "label");
  ASSERT_EQ(result[0].GetName(), "task");
}

TEST_F(TestTaskViewClass, shouldRemove){
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);
  ASSERT_TRUE(tv.RemoveTask(newTask));
  ASSERT_TRUE(tv.GetTasksByLabel("label").empty());
  ASSERT_TRUE(tv.GetTasksByName("name").empty());
  ASSERT_TRUE(tv.GetTasksByPriority(Priority::NONE).empty());
  ASSERT_TRUE(tv.GetTodayTasks().empty());
}
