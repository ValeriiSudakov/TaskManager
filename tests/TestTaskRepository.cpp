//
// Created by valerii.sudakov on 8/4/2020.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "Memory_Model/Storage/TaskRepository.h"

class TestTaskRepository : public ::testing::Test {
};

TEST_F(TestTaskRepository, shouldGetTaskView){
  TaskRepository tr;
  ASSERT_NE(&tr.GetTaskView(), nullptr);
}
TEST_F(TestTaskRepository, shouldGetTaskStorage){
  TaskRepository tr;
  ASSERT_NE(&tr.GetTaskStorage(), nullptr);
}

TEST_F(TestTaskRepository, shouldAddTask){
  TaskRepository tr;
  auto task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::Create(task->GetName(), task->GetLabel(), task->GetPriority(), task->GetDueDate());
  auto result = tr.AddTask(dto);

  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskRepository, shouldAddSubTask) {
  TaskRepository tr;
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::Create(task->GetName(), task->GetLabel(), task->GetPriority(), task->GetDueDate());
  tr.AddTask(dto);

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto subtaskDTO = TaskDTO::Create(task->GetName(), task->GetLabel(), task->GetPriority(), task->GetDueDate());
  auto result = tr.AddSubtask(tr.GetTaskView().GetTasksByName("task")[0].GetId(),subtaskDTO);


  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskRepository, shouldntAddSubTask) {
  TaskRepository tr;
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::Create(task->GetName(), task->GetLabel(), task->GetPriority(), task->GetDueDate());
  tr.AddTask(dto);

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto subtaskDTO = TaskDTO::Create(subTask->GetName(), subTask->GetLabel(), subTask->GetPriority(), subTask->GetDueDate());
  auto result = tr.AddSubtask(TaskID(2134515),subtaskDTO);


  ASSERT_FALSE(result.success_);
}

TEST_F(TestTaskRepository, shouldRemoveTask){
  TaskRepository tr;
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::Create(task->GetName(), task->GetLabel(), task->GetPriority(), task->GetDueDate());
  tr.AddTask(dto);

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto subtaskDTO = TaskDTO::Create(subTask->GetName(), subTask->GetLabel(), subTask->GetPriority(), subTask->GetDueDate());
  tr.AddSubtask(tr.GetTaskView().GetTasksByName("task")[0].GetId(),subtaskDTO);

  std::optional<Task> subTask1 = Task::Create("sub task1", "label", Priority::NONE, Date::GetCurrentTime());
  auto subtaskDTO1 = TaskDTO::Create(subTask1->GetName(), subTask1->GetLabel(), subTask1->GetPriority(), subTask1->GetDueDate());
  tr.AddSubtask(tr.GetTaskView().GetTasksByName("sub task")[0].GetId(),subtaskDTO1);


  ASSERT_TRUE(tr.RemoveTask(TaskID(0)));
  ASSERT_FALSE(tr.GetTaskStorage().GetTask(TaskID(0)).has_value());
  ASSERT_FALSE(tr.GetTaskStorage().GetTask(TaskID(1)).has_value());
  ASSERT_FALSE(tr.GetTaskStorage().GetTask(TaskID(2)).has_value());
}

TEST_F(TestTaskRepository, shouldntRemoveTask){
  TaskRepository tr;
  ASSERT_FALSE(tr.RemoveTask(TaskID(421)));
}
