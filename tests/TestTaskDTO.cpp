//
// Created by R2D2 on 29.07.2020.
//

#include <gtest/gtest.h>
#include "API/TaskDTO.h"
#include "Memory_Model/Date.h"
#include "Memory_Model/TaskIDGenerate.h"
#include <iostream>

class TestTaskDTOClass : public ::testing::Test {

};

TEST_F(TestTaskDTOClass, shouldCreateTaskDTO){
  TaskIDGenerate taskIDGenerate;
  tm date = Date::GetCurrentTime();
  std::optional<Task> task = Task::Create("task name", "label", Task::Priority::NONE, date);

  TaskDTO taskDTO(task.value(), false,  taskIDGenerate.Generate());

  ASSERT_EQ(taskDTO.GetTask().GetName(), "task name");
  ASSERT_EQ(taskDTO.GetTask().GetLabel(), "label");
  ASSERT_EQ(taskDTO.GetTask().GetPriority(), Task::Priority::NONE);
  tm date1 = taskDTO.GetTask().GetDueDate();
  ASSERT_EQ(mktime(&date1), mktime(&date));
  ASSERT_EQ(taskDTO.GetTaskId().GetID(),  0);
  ASSERT_EQ(taskDTO.IsTaskComplete(), false);

}