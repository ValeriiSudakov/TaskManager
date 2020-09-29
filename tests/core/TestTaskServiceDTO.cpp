//
// Created by R2D2 on 29.07.2020.
//

#include <gtest/gtest.h>
#include "API/TaskServiceDTO.h"
#include "Date/Date.h"
#include "Memory_Model/Task/TaskIDGenerate.h"
#include <iostream>
#include "Memory_Model/Task/Task.h"

class TestTaskServiceDTO : public ::testing::Test {

};

TEST_F(TestTaskServiceDTO, shouldCreateTaskDTO){
  TaskIDGenerate taskIDGenerate;
  Date date = Date::GetCurrentTime();
  TaskID id = taskIDGenerate.Generate();
  std::optional<Task> task = Task::Create("task name", "label", Priority::NONE, date);

  auto taskDTO = TaskServiceDTO::Create(task.value().GetName(), task.value().GetLabel(), task.value().GetPriority(),
                                                task.value().GetDueDate(), false, id);
  ASSERT_TRUE(taskDTO.has_value());


  ASSERT_EQ(taskDTO.value().GetName(), "task name");
  ASSERT_EQ(taskDTO.value().GetLabel(), "label");
  ASSERT_EQ(taskDTO.value().GetPriority(), Priority::NONE);
  Date date1 = taskDTO.value().GetDate();
  ASSERT_EQ(date.Get().day_number(), date1.Get().day_number());
  ASSERT_EQ(taskDTO.value().GetTaskId(),  id);
  ASSERT_EQ(taskDTO.value().IsTaskComplete(), false);

}