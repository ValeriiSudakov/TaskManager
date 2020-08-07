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
  auto task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto result = tr.AddTask(TaskDTO(task.value(), false, TaskID()), Task::Priority::NONE);
  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskRepository, shouldAddSubTask) {
  TaskRepository tr;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  TaskDTO newTask(task.value(), false, TaskID());
  tr.AddTask(newTask, Task::Priority::NONE);

  std::optional<Task> subTask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  TaskDTO newSubtask(task.value(), false, TaskID());
  auto result = tr.AddSubtask(tr.GetTaskView().GetTasksByName("task")[0].GetId(), newSubtask, Task::Priority::NONE);


  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskRepository, shouldntAddSubTask) {
  TaskRepository tr;
  std::optional<Task> task = Task::Create("task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  TaskDTO newTask(task.value(), false, TaskID());
  tr.AddTask(newTask, Task::Priority::NONE);

  std::optional<Task> subTask = Task::Create("sub task", "label", Task::Priority::NONE, Date::GetCurrentTime());
  TaskDTO newSubtask(task.value(), false, TaskID());
  auto result = tr.AddSubtask(TaskID(123), newSubtask, Task::Priority::NONE);

  ASSERT_FALSE(result.success_);
}
