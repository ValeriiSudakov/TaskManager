//
// Created by R2D2 on 29.07.2020.
//

#include <gtest/gtest.h>
#include "API/TaskDTO.h"
#include "API/Date/Date.h"
#include "Memory_Model/Task/TaskIDGenerate.h"
#include <iostream>

class TestTaskDTO : public ::testing::Test {

};

TEST_F(TestTaskDTO, shouldCreateTaskDTO){
  TaskIDGenerate taskIDGenerate;
  Date date = Date::GetCurrentTime();
  TaskID id = taskIDGenerate.Generate();
  std::optional<Task> task = Task::Create("task name", "label", Priority::NONE, date);

  auto taskDTO = TaskDTO::Create(task.value().GetName(), task.value().GetLabel(), task.value().GetPriority(),
                  task.value().GetDueDate(), false,  id);

  ASSERT_EQ(taskDTO.GetName(), "task name");
  ASSERT_EQ(taskDTO.GetLabel(), "label");
  ASSERT_EQ(taskDTO.GetPriority(), Priority::NONE);
  Date date1 = taskDTO.GetDate();
  ASSERT_EQ(date.Get().day_number(), date1.Get().day_number());
  ASSERT_EQ(taskDTO.GetTaskId(),  id);
  ASSERT_EQ(taskDTO.IsTaskComplete(), false);

}