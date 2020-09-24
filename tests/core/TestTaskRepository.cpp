//
// Created by valerii.sudakov on 8/4/2020.
//

#include <gtest/gtest.h>
#include "Memory_Model/Storage/TaskRepositoryClass.h"

class TestTaskRepository : public ::testing::Test {
};


TEST_F(TestTaskRepository, shouldAddTask){
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  auto task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto result = tr.AddTask(task.value());

  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskRepository, shouldAddSubTask) {
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  tr.AddTask(task.value());

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto result = tr.AddSubtask(tr.GetTaskView()->GetTasksByName("task")[0].GetId(),subTask.value());

  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskRepository, shouldntAddSubTask) {
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  tr.AddTask(task.value());

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto result = tr.AddSubtask(TaskID(2134515),subTask.value());


  ASSERT_FALSE(result.success_);
}

TEST_F(TestTaskRepository, shouldRemoveTask){
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  tr.AddTask(task.value());

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  tr.AddSubtask(tr.GetTaskView()->GetTasksByName("task")[0].GetId(),subTask.value());

  std::optional<Task> subTask1 = Task::Create("sub task1", "label", Priority::NONE, Date::GetCurrentTime());
  tr.AddSubtask(tr.GetTaskView()->GetTasksByName("sub task")[0].GetId(),subTask1.value());


  ASSERT_TRUE(tr.RemoveTask(TaskID(0)));
  ASSERT_FALSE(tr.GetTaskStorage()->GetTask(TaskID(0)).has_value());
  ASSERT_FALSE(tr.GetTaskStorage()->GetTask(TaskID(1)).has_value());
  ASSERT_FALSE(tr.GetTaskStorage()->GetTask(TaskID(2)).has_value());
}

TEST_F(TestTaskRepository, shouldntRemoveTask){
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  ASSERT_FALSE(tr.RemoveTask(TaskID(421)));
}
