//
// Created by R2D2 on 15.07.2020.
//

//
// Created by R2D2 on 15.07.2020.
//
#include <gtest/gtest.h>
#include "Memory_Model/Task/TaskEntity.h"
#include "API/TaskService.h"
#include "Memory_Model/Date.h"
#include <iostream>

class TestTaskEntityClass : public ::testing::Test {

};

TEST_F(TestTaskEntityClass, shouldCreateTask){
  TaskIDGenerate taskIDGenerate;
  auto task = Task::Create("task name", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(task.has_value());

  TaskEntity task_entity(task.value(),  taskIDGenerate.Generate());

  ASSERT_EQ(task_entity.GetTaskName(), "task name");
  ASSERT_EQ(task_entity.GetTaskLabel(),"label");

  ASSERT_EQ(Task::Priority::NONE, task_entity.GetTaskPriority());

  ASSERT_FALSE(task_entity.IsComplete());
  task_entity.SetComplete();
  ASSERT_TRUE(task_entity.IsComplete());
}

TEST_F(TestTaskEntityClass, shouldFailCreateTask){
  TaskIDGenerate taskIDGenerate;
  auto task = Task::Create("", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ASSERT_FALSE(task.has_value());

  std::optional<Task> task1 = Task::Create("task name", "", Task::Priority::NONE, Date::GetCurrentTime());
  ASSERT_FALSE(task.has_value());

  tm date = Date::GetCurrentTime();
  date.tm_mday--;
  std::optional<Task> task2 = Task::Create("task name", "label", Task::Priority::NONE, date);
  ASSERT_FALSE(task.has_value());

  std::optional<Task> task4 = Task::Create("", "", Task::Priority::NONE, date);
  ASSERT_FALSE(task.has_value());
}

TEST_F(TestTaskEntityClass, shouldBeCorrectData) {
  TaskIDGenerate taskIDGenerate;
  tm date = Date::GetCurrentTime();
  auto task = Task::Create("task", "label", Task::Priority::NONE, date);
  ASSERT_TRUE(task.has_value());

  ASSERT_EQ(task.value().GetName(), "task");
  ASSERT_EQ(task.value().GetLabel(), "label");
  ASSERT_EQ(task.value().GetPriority(), Task::Priority::NONE);
  tm taskDate = task.value().GetDueDate();
  ASSERT_EQ(mktime(&taskDate), mktime(&date));

}