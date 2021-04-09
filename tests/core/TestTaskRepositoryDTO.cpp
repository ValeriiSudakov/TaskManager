//
// Created by valeriisudakov on 29.07.2020.
//

#include <gtest/gtest.h>
#include "TaskRepositoryDTO.h"
#include "Date.h"
#include "TaskIDGenerate.h"
#include <iostream>
#include "Task.h"

class TestTaskRepositoryDTO : public ::testing::Test {

};

TEST_F(TestTaskRepositoryDTO, shouldCreateTaskRepositoryDTO){
  TaskIDGenerate taskIDGenerate;
  Date date = Date::GetCurrentTime();
  TaskID id = taskIDGenerate.Generate();
  std::optional<Task> task = Task::Create("task name", "label", Priority::NONE, date);

  auto taskDTO = TaskRepositoryDTO::Create(task.value().GetName(), task.value().GetLabel(), task.value().GetPriority(),
                                        task.value().GetDueDate(), false, id, id);

  ASSERT_EQ(taskDTO.value().GetName(), "task name");
  ASSERT_EQ(taskDTO.value().GetLabel(), "label");
  ASSERT_EQ(taskDTO.value().GetPriority(), Priority::NONE);
  Date date1 = taskDTO.value().GetDate();
  ASSERT_EQ(date.Get().day_number(), date1.Get().day_number());
  ASSERT_EQ(taskDTO.value().GetID(),  id);
  ASSERT_EQ(taskDTO.value().Complete(), false);

}