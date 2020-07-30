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

TEST_F(TestTaskEntityClass, testCreate){
  TaskIDGenerate taskIDGenerate;
  tm date = Date::CreateDate(11, 10, 2020, 3);
  Task task = Task::Create("task name", "label", Task::Priority::NONE, date);
  TaskEntity task_entity(task,  taskIDGenerate.Generate());

  ASSERT_EQ(task_entity.GetTaskName(), "task name");
  ASSERT_EQ(task_entity.GetTaskLabel(),"label");

  ASSERT_EQ(Task::Priority::NONE, task_entity.GetTaskPriority());

  task_entity.SetComplete();
  ASSERT_TRUE(task_entity.IsComplete());
}
