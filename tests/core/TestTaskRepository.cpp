//
// Created by valerii.sudakov on 8/4/2020.
//

#include <gtest/gtest.h>
#include "TaskRepositoryClass.h"

class TestTaskRepository : public ::testing::Test {
};

TaskRepositoryDTO ToDTO(Task& task){
  return TaskRepositoryDTO::Create(task.GetName(), task.GetLabel(), task.GetPriority(), task.GetDueDate()).value();
}

TEST_F(TestTaskRepository, shouldAddTask){
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  auto task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto result = tr.AddTask(ToDTO(task.value()));

  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskRepository, shouldAddSubTask) {
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  tr.AddTask(ToDTO(task.value()));

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto result = tr.AddSubtask(tr.GetTasksByName("task", false)[0].GetID(), ToDTO(subTask.value()));

  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskRepository, shouldntAddSubTask) {
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  tr.AddTask(ToDTO(task.value()));

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto result = tr.AddSubtask(TaskID(2134515),ToDTO(subTask.value()));


  ASSERT_FALSE(result.success_);
}

TEST_F(TestTaskRepository, shouldRemoveTask){
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  tr.AddTask(ToDTO(task.value()));

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  tr.AddSubtask(tr.GetTasksByName("task", false)[0].GetID(),ToDTO(subTask.value()));

  std::optional<Task> subTask1 = Task::Create("sub task1", "label", Priority::NONE, Date::GetCurrentTime());
  tr.AddSubtask(tr.GetTasksByName("sub task", false)[0].GetID(),ToDTO(subTask1.value()));


  ASSERT_TRUE(tr.RemoveTask(TaskID(0)));
  ASSERT_FALSE(tr.GetTask(TaskID(0)).has_value());
  ASSERT_FALSE(tr.GetTask(TaskID(1)).has_value());
  ASSERT_FALSE(tr.GetTask(TaskID(2)).has_value());
}

TEST_F(TestTaskRepository, shouldntRemoveTask){
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  ASSERT_FALSE(tr.RemoveTask(TaskID(421)));
}

TEST_F(TestTaskRepository, shouldSetComplete){
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  tr.AddTask(ToDTO(task.value()));

  auto uncompletedTask = tr.GetTask(TaskID(0));
  ASSERT_FALSE(uncompletedTask.value().Complete());

  ASSERT_FALSE(tr.SetTaskComplete(TaskID(412423512)));
  ASSERT_TRUE(tr.SetTaskComplete(TaskID(0)));

  auto completeTask = tr.GetTask(TaskID(0));
  ASSERT_TRUE(completeTask.value().Complete());

}