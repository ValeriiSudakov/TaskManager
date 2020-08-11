//
// Created by valerii.sudakov on 8/4/2020.
//

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
  auto dto = TaskDTO::CreateFromTask(task.value());
  auto result = tr.AddTask(dto, Priority::NONE);

  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskRepository, shouldAddSubTask) {
  TaskRepository tr;
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::CreateFromTask(task.value());
  tr.AddTask(dto, Priority::NONE);

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto subtaskDTO = TaskDTO::CreateFromTask(subTask.value());
  auto result = tr.AddSubtask(tr.GetTaskView().GetTasksByName("task")[0].GetId(),subtaskDTO, Priority::NONE);


  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskRepository, shouldntAddSubTask) {
  TaskRepository tr;
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::CreateFromTask(task.value());
  tr.AddTask(dto, Priority::NONE);

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto subtaskDTO = TaskDTO::CreateFromTask(subTask.value());
  auto result = tr.AddSubtask(TaskID(2134515),subtaskDTO, Priority::NONE);


  ASSERT_FALSE(result.success_);
}

TEST_F(TestTaskRepository, shouldRemoveTask){
  TaskRepository tr;
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::CreateFromTask(task.value());
  tr.AddTask(dto, Priority::NONE);

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto subtaskDTO = TaskDTO::CreateFromTask(subTask.value());
  tr.AddSubtask(tr.GetTaskView().GetTasksByName("task")[0].GetId(),subtaskDTO, Priority::NONE);

  std::optional<Task> subTask1 = Task::Create("sub task1", "label", Priority::NONE, Date::GetCurrentTime());
  auto subtaskDTO1 = TaskDTO::CreateFromTask(subTask.value());
  tr.AddSubtask(tr.GetTaskView().GetTasksByName("sub task")[0].GetId(),subtaskDTO1, Priority::NONE);


  ASSERT_TRUE(tr.RemoveTask(TaskID(0)));
  ASSERT_FALSE(tr.GetTaskStorage().GetTask(TaskID(0)).has_value());
  ASSERT_FALSE(tr.GetTaskStorage().GetTask(TaskID(1)).has_value());
  ASSERT_FALSE(tr.GetTaskStorage().GetTask(TaskID(2)).has_value());
}

TEST_F(TestTaskRepository, shouldntRemoveTask){
  TaskRepository tr;
  ASSERT_FALSE(tr.RemoveTask(TaskID(421)));
}
