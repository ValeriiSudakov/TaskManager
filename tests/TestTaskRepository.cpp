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
  tr.AddTask(task.value(), Task::Priority::NONE);
  auto temp = tr.GetTasks();
  ASSERT_FALSE(temp.empty());
}

TEST_F(TestTaskRepository, shoouldGetTaskByID){
  TaskRepository tr;
  auto task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  tr.AddTask(task.value(), Task::Priority::NONE);
  TaskID id(0);
  auto temp = tr.GetTask(id);
  ASSERT_TRUE(temp.has_value());
}


TEST_F(TestTaskRepository, shoouldntGetTaskByID){
  TaskRepository tr;
  auto task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  tr.AddTask(task.value(), Task::Priority::NONE);
  TaskID id(1252);
  auto temp = tr.GetTask(id);
  ASSERT_FALSE(temp.has_value());
}

TEST_F(TestTaskRepository, shouldAddSubtaskToRepository){
  TaskRepository tr;
  auto task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  tr.AddTask(task.value(), Task::Priority::NONE);

  TaskID id(0);
  auto subtask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto success = tr.AddSubtask(id, subtask.value(), Task::Priority::NONE);
  ASSERT_TRUE(success);
}

TEST_F(TestTaskRepository, shouldntAddSubtaskToRepository){
  TaskRepository tr;
  auto task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  tr.AddTask(task.value(), Task::Priority::NONE);

  auto subtask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  TaskID incorrectID(2121);
  auto success = tr.AddSubtask(incorrectID.GetID(), subtask.value(), Task::Priority::NONE);
  ASSERT_FALSE(success);
}


