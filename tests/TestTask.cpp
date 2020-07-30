//
// Created by R2D2 on 15.07.2020.
//

//
// Created by R2D2 on 15.07.2020.
//
#include <gtest/gtest.h>
#include "TaskEntity.h"
#include "TaskService.h"
#include "Date.h"
#include <iostream>

class TestTaskEntityClass : public ::testing::Test {

};

TEST_F(TestTaskEntityClass, shouldCreateTask){
  TaskIDGenerate taskIDGenerate;
  std::optional<Task> task = Task::Create("task name", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(task.has_value());

  TaskEntity task_entity(task.value(),  taskIDGenerate.Generate());

  ASSERT_EQ(task_entity.GetTaskName(), "task name");
  ASSERT_EQ(task_entity.GetTaskLabel(),"label");

  ASSERT_EQ(Task::Priority::NONE, task_entity.GetTaskPriority());

  ASSERT_FALSE(task_entity.IsComplete());
  task_entity.SetComplete();
  ASSERT_TRUE(task_entity.IsComplete());
}
