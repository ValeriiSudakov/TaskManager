//
// Created by R2D2 on 28.07.2020.
//

#include <gtest/gtest.h>
#include "TaskService.h"
#include <iostream>

class TestTaskViewClass : public ::testing::Test {

};

TEST_F(TestTaskViewClass, AddedToMaps){
  TaskView tv;
  TaskIDGenerate taskIDGenerate;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);
  auto result = tv.GetTasks();
  ASSERT_FALSE(result.empty());

}

TEST_F(TestTaskViewClass, GetNotSortedDate){
  TaskView tv;
  TaskIDGenerate taskIDGenerate;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);

  auto resultByName = tv.GetTasksByName("task");
  ASSERT_NE(resultByName.size(), 0);

  auto resultByLabel = tv.GetTasksByLabel("label");
  ASSERT_NE(resultByLabel.size(), 0);

  auto resultByPriority = tv.GetTasksByPriority(Task::Priority::NONE);
  ASSERT_NE(resultByPriority.size(), 0);

  auto resultForToday = tv.GetTodayTasks();
  ASSERT_NE(resultForToday.size(), 0);
}

TEST_F(TestTaskViewClass, GetSortedDate){
  TaskView tv;
  TaskIDGenerate taskIDGenerate;

  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);

  auto resultByName = tv.GetTasksByName("task");
  ASSERT_NE(resultByName.size(), 0);

  auto resultByLabel = tv.GetTasksByLabel("label");
  ASSERT_NE(resultByLabel.size(), 0);

  auto resultByPriority = tv.GetTasksByPriority(Task::Priority::NONE);
  ASSERT_NE(resultByPriority.size(), 0);

  auto resultForToday = tv.GetTodayTasks();
  ASSERT_NE(resultForToday.size(), 0);
}