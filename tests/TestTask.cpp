//
// Created by R2D2 on 15.07.2020.
//

//
// Created by R2D2 on 15.07.2020.
//
#include <gtest/gtest.h>
#include "Memory_Model/Task/TaskEntity.h"
#include "API/TaskService.h"
#include "API/Priority.h"
#include "API/Date/Date.h"
#include <iostream>

class TestTaskEntity : public ::testing::Test {

};

TEST_F(TestTaskEntity, shouldCreateTask){
  TaskIDGenerate taskIDGenerate;
  auto task = Task::Create("task name", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(task.has_value());

  TaskEntity task_entity(task.value(),  taskIDGenerate.Generate());

  ASSERT_EQ(task_entity.GetName(), "task name");
  ASSERT_EQ(task_entity.GetLabel(),"label");

  ASSERT_EQ(Priority::NONE, task_entity.GetPriority());

  ASSERT_FALSE(task_entity.IsComplete());
}

TEST_F(TestTaskEntity, shouldFailCreateTask){
  TaskIDGenerate taskIDGenerate;
  auto task = Task::Create("", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_FALSE(task.has_value());

  std::optional<Task> task1 = Task::Create("task name", "", Priority::NONE, Date::GetCurrentTime());
  ASSERT_FALSE(task.has_value());

  Date date("2000-1-1");
  std::optional<Task> task2 = Task::Create("task name", "label", Priority::NONE, date);
  ASSERT_FALSE(task.has_value());

  std::optional<Task> task4 = Task::Create("", "", Priority::NONE, date);
  ASSERT_FALSE(task.has_value());
}

TEST_F(TestTaskEntity, shouldBeCorrectData) {
  TaskIDGenerate taskIDGenerate;
  Date date = Date::GetCurrentTime();
  auto task = Task::Create("task", "label", Priority::NONE, date);
  ASSERT_TRUE(task.has_value());

  ASSERT_EQ(task.value().GetName(), "task");
  ASSERT_EQ(task.value().GetLabel(), "label");
  ASSERT_EQ(task.value().GetPriority(), Priority::NONE);
  Date taskDate = task.value().GetDueDate();
  ASSERT_EQ(taskDate.Get().day_number(), date.Get().day_number());

}

TEST_F(TestTaskEntity, shouldComplite){
  TaskIDGenerate taskIDGenerate;
  auto task = Task::Create("task name", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(task.has_value());
  TaskEntity task_entity(task.value(),  taskIDGenerate.Generate());

  auto subTask = Task::Create("task name", "label", Priority::NONE, Date::GetCurrentTime());
  auto ptrSubtask = std::make_shared<TaskEntity>(subTask.value(), TaskID(0), taskIDGenerate.Generate());
  task_entity.AddSubtasks(ptrSubtask);
  ASSERT_FALSE(task_entity.IsComplete());
  task_entity.SetComplete();
  ASSERT_TRUE(task_entity.IsComplete());
}

TEST_F(TestTaskEntity, shouldGetParentID){
    TaskIDGenerate taskIDGenerate;
    auto task = Task::Create("task name", "label", Priority::NONE, Date::GetCurrentTime());
    ASSERT_TRUE(task.has_value());
    TaskEntity task_entity(task.value(),  taskIDGenerate.Generate());

    auto subTask = Task::Create("task name", "label", Priority::NONE, Date::GetCurrentTime());
    auto ptrSubtask = std::make_shared<TaskEntity>(subTask.value(), taskIDGenerate.Generate(), task_entity.GetId());
    task_entity.AddSubtasks(ptrSubtask);

    ASSERT_EQ(task_entity.GetId().Get(), task_entity.GetParentId().Get());
    auto parentIDofSubtask = task_entity.GetSubtasks().begin()->second.lock()->GetParentId();
    ASSERT_EQ(task_entity.GetId().Get(), parentIDofSubtask.Get());

}

TEST_F(TestTaskEntity, shouldRemoveSubtas){
    TaskIDGenerate taskIDGenerate;
    auto task = Task::Create("task name", "label", Priority::NONE, Date::GetCurrentTime());
    ASSERT_TRUE(task.has_value());
    TaskEntity task_entity(task.value(),  taskIDGenerate.Generate());

    auto subTask = Task::Create("task name", "label", Priority::NONE, Date::GetCurrentTime());
    auto ptrSubtask = std::make_shared<TaskEntity>(subTask.value(), taskIDGenerate.Generate(), task_entity.GetId());
    task_entity.AddSubtasks(ptrSubtask);
    auto result = task_entity.RemoveTaskFromSubtasks(TaskID(1));
    ASSERT_TRUE(result);
}

TEST_F(TestTaskEntity, shouldntRemoveSubtas){
    TaskIDGenerate taskIDGenerate;
    auto task = Task::Create("task name", "label", Priority::NONE, Date::GetCurrentTime());
    ASSERT_TRUE(task.has_value());
    TaskEntity task_entity(task.value(),  taskIDGenerate.Generate());
    auto result = task_entity.RemoveTaskFromSubtasks(TaskID(21311));
    ASSERT_FALSE(result);
}

TEST_F(TestTaskEntity, shouldPostpone){
    TaskIDGenerate taskIDGenerate;
    auto task = Task::Create("task name", "label", Priority::NONE, Date::GetCurrentTime());
    ASSERT_TRUE(task.has_value());
    TaskEntity task_entity(task.value(),  taskIDGenerate.Generate());
    boost::gregorian::date rawDate(Date::GetCurrentTime().day_number() + 5);
    Date date(rawDate);
    ASSERT_TRUE(task_entity.PostponeDate(date));
}

TEST_F(TestTaskEntity, shouldntPostpone){
    TaskIDGenerate taskIDGenerate;
    auto task = Task::Create("task name", "label", Priority::NONE, Date::GetCurrentTime());
    ASSERT_TRUE(task.has_value());
    TaskEntity task_entity(task.value(),  taskIDGenerate.Generate());
    boost::gregorian::date rawDate(Date::GetCurrentTime().day_number() - 5);
    Date date(rawDate);
    ASSERT_FALSE(task_entity.PostponeDate(date));
}