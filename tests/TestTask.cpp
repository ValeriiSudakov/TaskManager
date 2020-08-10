//
// Created by R2D2 on 15.07.2020.
//

//
// Created by R2D2 on 15.07.2020.
//
#include <gtest/gtest.h>
#include "Memory_Model/Task/TaskEntity.h"
#include "API/TaskService.h"
#include "Memory_Model/Date/Date.h"
#include <iostream>

class TestTaskEntityClass : public ::testing::Test {

};

TEST_F(TestTaskEntityClass, shouldCreateTask){
  TaskIDGenerate taskIDGenerate;
  auto task = Task::Create("task name", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(task.has_value());

  TaskEntity task_entity(task.value(),  taskIDGenerate.Generate());

  ASSERT_EQ(task_entity.GetTaskName(), "task name");
  ASSERT_EQ(task_entity.GetTaskLabel(),"label");

  ASSERT_EQ(Task::Priority::NONE, task_entity.GetTaskPriority());

  ASSERT_FALSE(task_entity.IsComplete());
}

TEST_F(TestTaskEntityClass, shouldFailCreateTask){
  TaskIDGenerate taskIDGenerate;
  auto task = Task::Create("", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ASSERT_FALSE(task.has_value());

  std::optional<Task> task1 = Task::Create("task name", "", Task::Priority::NONE, Date::GetCurrentTime());
  ASSERT_FALSE(task.has_value());

  Date date("2000-1-1");
  std::optional<Task> task2 = Task::Create("task name", "label", Task::Priority::NONE, date);
  ASSERT_FALSE(task.has_value());

  std::optional<Task> task4 = Task::Create("", "", Task::Priority::NONE, date);
  ASSERT_FALSE(task.has_value());
}

TEST_F(TestTaskEntityClass, shouldBeCorrectData) {
  TaskIDGenerate taskIDGenerate;
  Date date = Date::GetCurrentTime();
  auto task = Task::Create("task", "label", Task::Priority::NONE, date);
  ASSERT_TRUE(task.has_value());

  ASSERT_EQ(task.value().GetName(), "task");
  ASSERT_EQ(task.value().GetLabel(), "label");
  ASSERT_EQ(task.value().GetPriority(), Task::Priority::NONE);
  Date taskDate = task.value().GetDueDate();
  ASSERT_EQ(taskDate.Get().day_number(), date.Get().day_number());

}

TEST_F(TestTaskEntityClass, shouldComplite){
  TaskIDGenerate taskIDGenerate;
  auto task = Task::Create("task name", "label", Task::Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(task.has_value());
  TaskEntity task_entity(task.value(),  taskIDGenerate.Generate());

  auto subTask = Task::Create("task name", "label", Task::Priority::NONE, Date::GetCurrentTime());
  auto ptrSubtask = std::make_shared<TaskEntity>(subTask.value(), TaskID(0), taskIDGenerate.Generate());
  task_entity.AddSubtasks(ptrSubtask);
  ASSERT_FALSE(task_entity.IsComplete());
  task_entity.SetComplete();
  ASSERT_TRUE(task_entity.IsComplete());
}

TEST_F(TestTaskEntityClass, shouldGetParentID){
    TaskIDGenerate taskIDGenerate;
    auto task = Task::Create("task name", "label", Task::Priority::NONE, Date::GetCurrentTime());
    ASSERT_TRUE(task.has_value());
    TaskEntity task_entity(task.value(),  taskIDGenerate.Generate());

    auto subTask = Task::Create("task name", "label", Task::Priority::NONE, Date::GetCurrentTime());
    auto ptrSubtask = std::make_shared<TaskEntity>(subTask.value(), taskIDGenerate.Generate(), task_entity.GetId());
    task_entity.AddSubtasks(ptrSubtask);

    ASSERT_EQ(task_entity.GetId().GetID(), task_entity.GetParentId().GetID());
    auto parentIDofSubtask = task_entity.GetSubtasks().begin()->second.lock()->GetParentId();
    ASSERT_EQ(task_entity.GetId().GetID(), parentIDofSubtask.GetID());

}

TEST_F(TestTaskEntityClass, shouldRemoveSubtas){
    TaskIDGenerate taskIDGenerate;
    auto task = Task::Create("task name", "label", Task::Priority::NONE, Date::GetCurrentTime());
    ASSERT_TRUE(task.has_value());
    TaskEntity task_entity(task.value(),  taskIDGenerate.Generate());

    auto subTask = Task::Create("task name", "label", Task::Priority::NONE, Date::GetCurrentTime());
    auto ptrSubtask = std::make_shared<TaskEntity>(subTask.value(), taskIDGenerate.Generate(), task_entity.GetId());
    task_entity.AddSubtasks(ptrSubtask);
    auto result = task_entity.RemoveTaskFromSubtasks(TaskID(1));
    ASSERT_TRUE(result);
}

TEST_F(TestTaskEntityClass, shouldntRemoveSubtas){
    TaskIDGenerate taskIDGenerate;
    auto task = Task::Create("task name", "label", Task::Priority::NONE, Date::GetCurrentTime());
    ASSERT_TRUE(task.has_value());
    TaskEntity task_entity(task.value(),  taskIDGenerate.Generate());
    auto result = task_entity.RemoveTaskFromSubtasks(TaskID(21311));
    ASSERT_FALSE(result);
}