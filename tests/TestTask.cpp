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

  Date date = TaskService::CreateDate(11, 10, 2020, 3);
  Date date1 = TaskService::CreateDate(22, 1, 2020, 2);

  Task task = Task::Create("task name", "label", Task::Priority::HIGH, date.GetDate());
  auto taskPtr = std::make_shared<Task>(task);
  TaskEntity task_entity(taskPtr, 1);

  ASSERT_EQ(task_entity.GetTaskName(), "task name");
  ASSERT_EQ(task_entity.GetTaskLabel(),"label");

  ASSERT_EQ(Task::Priority::HIGH, task_entity.GetTaskPriority());

  ASSERT_LE(task_entity.GetTaskDueDate().tm_wday, 6);
  ASSERT_GE(task_entity.GetTaskDueDate().tm_wday, 0);

  ASSERT_LE(task_entity.GetTaskDueDate().tm_mday, 31);
  ASSERT_GE(task_entity.GetTaskDueDate().tm_mday, 1);

  ASSERT_LE(task_entity.GetTaskDueDate().tm_mon, 11);
  ASSERT_GE(task_entity.GetTaskDueDate().tm_mon, 0);

  task_entity.SetComplete();
  ASSERT_TRUE(task_entity.IsComplete());
}
