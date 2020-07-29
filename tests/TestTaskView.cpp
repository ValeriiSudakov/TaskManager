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

TEST_F(TestTaskViewClass, GetByName){
  TaskView tv;
  TaskID taskID;

  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task, taskID.GenerateID());
  tv.AddTask(newTask);

  auto resultByNameSorted = tv.GetTasksByName("task", false);
  ASSERT_FALSE(resultByNameSorted.empty());
}

TEST_F(TestTaskViewClass, GetByLabel){
  TaskView tv;
  TaskID taskID;

  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task, taskID.GenerateID());
  tv.AddTask(newTask);

  auto resultByLabelNotSorted = tv.GetTasksByLabel("label", false);
  ASSERT_FALSE(resultByLabelNotSorted.empty());
}

TEST_F(TestTaskViewClass, GetByPriority){
  TaskView tv;
  TaskID taskID;

  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task, taskID.GenerateID());
  tv.AddTask(newTask);

  auto resultByPriority = tv.GetTasksByPriority(Task::Priority::HIGH);
  ASSERT_FALSE(resultByPriority.empty());
}


