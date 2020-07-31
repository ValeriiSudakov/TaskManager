//
// Created by R2D2 on 31.07.2020.
//

#include <gtest/gtest.h>
#include "API/TaskService.h"

class TestTaskRepository : public ::testing::Test {

};

TEST_F(TestTaskRepository, shouldAddTaskToRepository){
  TaskRepository tr;
  auto task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto result = tr.AddTask(task.value(), Task::Priority::NONE);
  ASSERT_TRUE(result.lock() );
}

TEST_F(TestTaskRepository, shouldAddSubtaskToRepository){
  TaskRepository tr;
  auto task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto taskEntity = tr.AddTask(task.value(), Task::Priority::NONE);

  auto subtask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto subtaskEntity = tr.AddSubtask(taskEntity.lock()->GetId().GetID(), subtask.value(), Task::Priority::NONE);
  ASSERT_TRUE(subtaskEntity.has_value());
}

TEST_F(TestTaskRepository, shouldntAddSubtaskToRepository){
  TaskRepository tr;
  auto task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto taskEntity = tr.AddTask(task.value(), Task::Priority::NONE);

  auto subtask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  TaskID incorrectID(2121);
  auto subtaskEntity = tr.AddSubtask(incorrectID.GetID(), subtask.value(), Task::Priority::NONE);
  ASSERT_FALSE(subtaskEntity.has_value());
}


