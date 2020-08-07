//
// Created by R2D2 on 29.07.2020.
//

#include <gtest/gtest.h>
#include "API/TaskDTO.h"
#include "Memory_Model/Date/Date.h"
#include "Memory_Model/Task/TaskIDGenerate.h"
#include <iostream>

class TestTaskDTOClass : public ::testing::Test {

};

TEST_F(TestTaskDTOClass, shouldCreateTaskDTO){
  TaskIDGenerate taskIDGenerate;
  Date date = Date::GetCurrentTime();
  std::optional<Task> task = Task::Create("task name", "label", Task::Priority::NONE, date);

  TaskDTO taskDTO(task.value(), false,  taskIDGenerate.Generate());

  ASSERT_EQ(taskDTO.GetTask().GetName(), "task name");
  ASSERT_EQ(taskDTO.GetTask().GetLabel(), "label");
  ASSERT_EQ(taskDTO.GetTask().GetPriority(), Task::Priority::NONE);
  Date date1 = taskDTO.GetTask().GetDueDate();
  ASSERT_EQ(date.Get().day_number(), date1.Get().day_number());
  ASSERT_EQ(taskDTO.GetTaskId().GetID(),  0);
  ASSERT_EQ(taskDTO.IsTaskComplete(), false);

}