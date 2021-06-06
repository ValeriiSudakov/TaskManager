//
// Created by valeriisudakov on 28.07.2020.
//

#include <gtest/gtest.h>
#include "TaskRepositoryClass.h"
#include <iostream>

class TestTaskView : public ::testing::Test {

 protected:
  TaskViewClass tv;
  TaskIDGenerate taskIDGenerate;
};

TEST_F(TestTaskView, shouldAddTask){
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);
  auto result = tv.GetTasks();
  ASSERT_FALSE(result.empty());
}

TEST_F(TestTaskView, shouldGetData){
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);
  auto resultByName = tv.GetTasksByName("task");
  ASSERT_FALSE(resultByName.empty());

  auto resultByLabel = tv.GetTasksByLabel("label");
  ASSERT_FALSE(resultByLabel.empty());

  auto resultByPriority = tv.GetTasksByPriority(Priority::NONE);
  ASSERT_FALSE(resultByPriority.empty());

  auto resultForToday = tv.GetTodayTasks();
  ASSERT_FALSE(resultForToday.empty());
}

TEST_F(TestTaskView, shouldntGetData){
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);
  auto resultByName = tv.GetTasksByName("");
  ASSERT_TRUE(resultByName.empty());

  auto resultByLabel = tv.GetTasksByLabel("");
  ASSERT_TRUE(resultByLabel.empty());

  auto resultByPriority = tv.GetTasksByPriority(Priority::FIRST);
  ASSERT_TRUE(resultByPriority.empty());
}

TEST_F(TestTaskView, shouldGetWeekTasks){
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);
  auto resultThisWeek = tv.GetWeekTasks();
  ASSERT_FALSE(resultThisWeek.empty());
  ASSERT_EQ(resultThisWeek.size(), 1);

  std::optional<Task> task1 = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto newTask1 = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask1);
  auto resultThisWeek1 = tv.GetWeekTasks();
  ASSERT_NE(resultThisWeek1.size(), resultThisWeek.size());
  ASSERT_EQ(resultThisWeek1.size(), 2);
}

TEST_F(TestTaskView, shouldGetTasksByDate){
  auto current_date = Date::GetCurrentTime();
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, current_date);
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);

  auto resultThisWeek = tv.GetTasksByDate(current_date);
  ASSERT_FALSE(resultThisWeek.empty());
  ASSERT_EQ(resultThisWeek.size(), 1);
}

TEST_F(TestTaskView, shouldntGetTasksByDate) {
  {
    Date date(boost::gregorian::date(Date::GetCurrentTime().day_number() + 1));
    std::optional<Task> task = Task::Create("task", "label", Priority::NONE, date);
    auto newTask = std::make_shared<TaskEntity>(task.value(), taskIDGenerate.Generate());
    tv.AddTask(newTask);
  }
  {
    Date date(boost::gregorian::date(Date::GetCurrentTime().day_number() - 1));
    std::optional<Task> task = Task::Create("task", "label", Priority::NONE, date);
    auto newTask = std::make_shared<TaskEntity>(task.value(), taskIDGenerate.Generate());
    tv.AddTask(newTask);
  }
  auto resultByDate = tv.GetTasksByDate(Date::GetCurrentTime());
  ASSERT_TRUE(resultByDate.empty());
  ASSERT_EQ(resultByDate.size(), 0);
}

TEST_F(TestTaskView, shouldGetCorrectTaskData){
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);
  TaskIDGenerate taskIDGenerate;
  TaskID id(taskIDGenerate.Generate());
  auto result = tv.GetTasks();
  ASSERT_FALSE(result.empty());

  ASSERT_FALSE(result[0].IsComplete());
  ASSERT_EQ(result[0].GetId(), id);
  ASSERT_EQ(result[0].GetPriority(), Priority::NONE);
  ASSERT_EQ(result[0].GetLabel(), "label");
  ASSERT_EQ(result[0].GetName(), "task");
}

TEST_F(TestTaskView, shouldRemove){
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto newTask = std::make_shared<TaskEntity>(task.value(),  taskIDGenerate.Generate());
  tv.AddTask(newTask);
  ASSERT_TRUE(tv.RemoveTask(newTask));
  ASSERT_TRUE(tv.GetTasksByLabel("label").empty());
  ASSERT_TRUE(tv.GetTasksByName("name").empty());
  ASSERT_TRUE(tv.GetTasksByPriority(Priority::NONE).empty());
  ASSERT_TRUE(tv.GetTodayTasks().empty());
}
