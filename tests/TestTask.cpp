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

  TaskID taskID;
  tm date = Date::CreateDate(11, 10, 2020, 3);
  Task task = Task::Create("task name", "label", Task::Priority::HIGH, date);
  TaskEntity task_entity(task, taskID.GenerateID());

  ASSERT_EQ(task_entity.GetTaskName(), "task name");
  ASSERT_EQ(task_entity.GetTaskLabel(),"label");

  ASSERT_EQ(Task::Priority::HIGH, task_entity.GetTaskPriority());

  task_entity.SetComplete();
  ASSERT_TRUE(task_entity.IsComplete());
}
