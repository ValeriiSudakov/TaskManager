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
  TaskID taskID;

  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task, taskID.GenerateID());
  tv.AddTask(newTask);
  auto result = tv.GetTasks(false);
  ASSERT_FALSE(result.empty());

}

TEST_F(TestTaskViewClass, GetNotSortedDate){
  TaskView tv;
  TaskID taskID;

  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task, taskID.GenerateID());
  tv.AddTask(newTask);

  auto resultByName = tv.GetTasksByName("task", false);
  ASSERT_NE(resultByName.size(), 0);

  auto resultByLabel = tv.GetTasksByLabel("label", false);
  ASSERT_NE(resultByLabel.size(), 0);

  auto resultByPriority = tv.GetTasksByPriority(Task::Priority::HIGH);
  ASSERT_NE(resultByPriority.size(), 0);

  auto resultForToday = tv.GetTodayTasks(false);
  ASSERT_NE(resultForToday.size(), 0);
}

TEST_F(TestTaskViewClass, GetSortedDate){
  TaskView tv;
  TaskID taskID;

  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task, taskID.GenerateID());
  tv.AddTask(newTask);

  auto resultByName = tv.GetTasksByName("task", true);
  ASSERT_NE(resultByName.size(), 0);

  auto resultByLabel = tv.GetTasksByLabel("label", true);
  ASSERT_NE(resultByLabel.size(), 0);

  auto resultByPriority = tv.GetTasksByPriority(Task::Priority::HIGH);
  ASSERT_NE(resultByPriority.size(), 0);

  auto resultForToday = tv.GetTodayTasks(true);
  ASSERT_NE(resultForToday.size(), 0);
}