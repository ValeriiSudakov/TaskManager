//
// Created by R2D2 on 28.07.2020.
//

#include <gtest/gtest.h>
#include "TaskService.h"
#include <iostream>

class TestTaskViewClass : public ::testing::Test {

};

TEST_F(TestTaskViewClass, shouldAddTask){
  TaskView tv;
  TaskIDGenerate taskIDGenerate;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);
  auto result = tv.GetTasks();
  ASSERT_FALSE(result.empty());
}

TEST_F(TestTaskViewClass, shouldGetData){
  TaskView tv;
  TaskIDGenerate taskIDGenerate;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);

  auto resultByName = tv.GetTasksByName("task");
  ASSERT_FALSE(resultByName.empty());

  auto resultByLabel = tv.GetTasksByLabel("label");
  ASSERT_FALSE(resultByLabel.empty());

  auto resultByPriority = tv.GetTasksByPriority(Task::Priority::NONE);
  ASSERT_FALSE(resultByPriority.empty());

  auto resultForToday = tv.GetTodayTasks();
  ASSERT_FALSE(resultForToday.empty());
}

TEST_F(TestTaskViewClass, shouldntGetData){
  TaskView tv;
  TaskIDGenerate taskIDGenerate;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);

  auto resultByName = tv.GetTasksByName("");
  ASSERT_TRUE(resultByName.empty());

  auto resultByLabel = tv.GetTasksByLabel("");
  ASSERT_TRUE(resultByLabel.empty());

  auto resultByPriority = tv.GetTasksByPriority(Task::Priority::FIRST);
  ASSERT_TRUE(resultByPriority.empty());
}

TEST_F(TestTaskViewClass, shouldGetCorrectTaskData){
  TaskView tv;
  TaskIDGenerate taskIDGenerate;
  TaskID id(taskIDGenerate.Generate());
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  id);
  tv.AddTask(newTask);
  auto result = tv.GetTasks();
  ASSERT_FALSE(result.empty());

  ASSERT_FALSE(result[0].IsComplete());
  ASSERT_EQ(result[0].GetId().GetID(), id.GetID());
  ASSERT_EQ(result[0].GetTaskPriority(), Task::Priority::NONE);
  ASSERT_EQ(result[0].GetTaskLabel(), "label");
  ASSERT_EQ(result[0].GetTaskName(), "task");
}
